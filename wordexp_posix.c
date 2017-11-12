/* POSIX.2 wordexp implementation.
   Copyright (C) 1997-2017 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Tim Waugh <tim@cyberelk.demon.co.uk>.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <alloca.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <fnmatch.h>
#include <glob.h>
#include <libintl.h>
#include <paths.h>
#include <pwd.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <wchar.h>
#include <wordexp.h>
#include <kernel-features.h>

#include <libc-lock.h>
#include <_itoa.h>

/* Undefine the following line for the production version.  */
/* #define NDEBUG 1 */
#include <assert.h>

/* Get some device information.  */
#include <device-nrs.h>

/*
 * This is a recursive-descent-style word expansion routine.
 */

/* These variables are defined and initialized in the startup code.  */
extern int __libc_argc attribute_hidden;
extern char **__libc_argv attribute_hidden;

/* Some forward declarations */
static int parse_dollars (char **word, size_t *word_length, size_t *max_length,
                          const char *words, size_t *offset, int flags,
                          wordexp_t *pwordexp, const char *ifs,
                          const char *ifs_white, int quoted);
static int parse_backtick (char **word, size_t *word_length,
                           size_t *max_length, const char *words,
                           size_t *offset, int flags, wordexp_t *pwordexp,
                           const char *ifs, const char *ifs_white);
static int parse_dquote (char **word, size_t *word_length, size_t *max_length,
                         const char *words, size_t *offset, int flags,
                         wordexp_t *pwordexp, const char *ifs,
                         const char *ifs_white);
static int eval_expr (char *expr, long int *result);

/* The w_*() functions manipulate word lists. */

#define W_CHUNK        (100)

/* Result of w_newword will be ignored if it's the last word. */
static inline char *
w_newword (size_t *actlen, size_t *maxlen)
{
  *actlen = *maxlen = 0;
  return NULL;
}

static char *
w_addchar (char *buffer, size_t *actlen, size_t *maxlen, char ch)
     /* (lengths exclude trailing zero) */
{
  /* Add a character to the buffer, allocating room for it if needed.  */

  if (*actlen == *maxlen)
    {
      char *old_buffer = buffer;
      assert (buffer == NULL || *maxlen != 0);
      *maxlen += W_CHUNK;
      buffer = (char *) realloc (buffer, 1 + *maxlen);

      if (buffer == NULL)
        free (old_buffer);
    }

  if (buffer != NULL)
    {
      buffer[*actlen] = ch;
      buffer[++(*actlen)] = '\0';
    }

  return buffer;
}

static char *
w_addmem (char *buffer, size_t *actlen, size_t *maxlen, const char *str,
          size_t len)
{
  /* Add a string to the buffer, allocating room for it if needed.
   */
  if (*actlen + len > *maxlen)
    {
      char *old_buffer = buffer;
      assert (buffer == NULL || *maxlen != 0);
      *maxlen += MAX (2 * len, W_CHUNK);
      buffer = realloc (old_buffer, 1 + *maxlen);

      if (buffer == NULL)
        free (old_buffer);
    }

  if (buffer != NULL)
    {
      *((char *) __mempcpy (&buffer[*actlen], str, len)) = '\0';
      *actlen += len;
    }

  return buffer;
}

static char *
w_addstr (char *buffer, size_t *actlen, size_t *maxlen, const char *str)
     /* (lengths exclude trailing zero) */
{
  /* Add a string to the buffer, allocating room for it if needed.
   */
  size_t len;

  assert (str != NULL); /* w_addstr only called from this file */
  len = strlen (str);

  return w_addmem (buffer, actlen, maxlen, str, len);
}

static int
w_addword (wordexp_t *pwordexp, char *word)
{
  /* Add a word to the wordlist */
  size_t num_p;
  char **new_wordv;
  bool allocated = false;

  /* Internally, NULL acts like "".  Convert NULLs to "" before
   * the caller sees them.
   */
  if (word == NULL)
    {
      word = __strdup ("");
      if (word == NULL)
        goto no_space;
      allocated = true;
    }

  num_p = 2 + pwordexp->we_wordc + pwordexp->we_offs;
  new_wordv = realloc (pwordexp->we_wordv, sizeof (char *) * num_p);
  if (new_wordv != NULL)
    {
      pwordexp->we_wordv = new_wordv;
      pwordexp->we_wordv[pwordexp->we_offs + pwordexp->we_wordc++] = word;
      pwordexp->we_wordv[pwordexp->we_offs + pwordexp->we_wordc] = NULL;
      return 0;
    }

  if (allocated)
    free (word);

no_space:
  return WRDE_NOSPACE;
}

/* The parse_*() functions should leave *offset being the offset in 'words'
 * to the last character processed.
 */

static int
parse_backslash (char **word, size_t *word_length, size_t *max_length,
                 const char *words, size_t *offset)
{
  /* We are poised _at_ a backslash, not in quotes */

  switch (words[1 + *offset])
    {
    case 0:
      /* Backslash is last character of input words */
      return WRDE_SYNTAX;

    case '\n':
      ++(*offset);
      break;

    default:
      *word = w_addchar (*word, word_length, max_length, words[1 + *offset]);
      if (*word == NULL)
        return WRDE_NOSPACE;

      ++(*offset);
      break;
    }

  return 0;
}

static int
parse_qtd_backslash (char **word, size_t *word_length, size_t *max_length,
                     const char *words, size_t *offset)
{
  /* We are poised _at_ a backslash, inside quotes */

  switch (words[1 + *offset])
    {
    case 0:
      /* Backslash is last character of input words */
      return WRDE_SYNTAX;

    case '\n':
      ++(*offset);
      break;

    case '$':
    case '`':
    case '"':
    case '\\':
      *word = w_addchar (*word, word_length, max_length, words[1 + *offset]);
      if (*word == NULL)
        return WRDE_NOSPACE;

      ++(*offset);
      break;

    default:
      *word = w_addchar (*word, word_length, max_length, words[*offset]);
      if (*word != NULL)
        *word = w_addchar (*word, word_length, max_length, words[1 + *offset]);

      if (*word == NULL)
        return WRDE_NOSPACE;

      ++(*offset);
      break;
    }

  return 0;
}

static int
parse_tilde (char **word, size_t *word_length, size_t *max_length,
             const char *words, size_t *offset, size_t wordc)
{
  /* We are poised _at_ a tilde */
  size_t i;

  if (*word_length != 0)
    {
      if (!((*word)[*word_length - 1] == '=' && wordc == 0))
        {
          if (!((*word)[*word_length - 1] == ':'
                && strchr (*word, '=') && wordc == 0))
            {
              *word = w_addchar (*word, word_length, max_length, '~');
              return *word ? 0 : WRDE_NOSPACE;
            }
        }
    }

  for (i = 1 + *offset; words[i]; i++)
    {
      if (words[i] == ':' || words[i] == '/' || words[i] == ' ' ||
          words[i] == '\t' || words[i] == 0 )
        break;

      if (words[i] == '\\')
        {
          *word = w_addchar (*word, word_length, max_length, '~');
          return *word ? 0 : WRDE_NOSPACE;
        }
    }

  if (i == 1 + *offset)
    {
      /* Tilde appears on its own */
      uid_t uid;
      struct passwd pwd, *tpwd;
      int buflen = 1000;
      char* home;
      char* buffer;
      int result;

      /* POSIX.2 says ~ expands to $HOME and if HOME is unset the
         results are unspecified.  We do a lookup on the uid if
         HOME is unset. */

      home = getenv ("HOME");
      if (home != NULL)
        {
          *word = w_addstr (*word, word_length, max_length, home);
          if (*word == NULL)
            return WRDE_NOSPACE;
        }
      else
        {
          uid = __getuid ();
          buffer = __alloca (buflen);

          while ((result = __getpwuid_r (uid, &pwd, buffer, buflen, &tpwd)) != 0
                 && errno == ERANGE)
            buffer = extend_alloca (buffer, buflen, buflen + 1000);

          if (result == 0 && tpwd != NULL && pwd.pw_dir != NULL)
            {
              *word = w_addstr (*word, word_length, max_length, pwd.pw_dir);
              if (*word == NULL)
                return WRDE_NOSPACE;
            }
          else
            {
              *word = w_addchar (*word, word_length, max_length, '~');
              if (*word == NULL)
                return WRDE_NOSPACE;
            }
        }
    }
  else
    {
      /* Look up user name in database to get home directory */
      char *user = strndupa (&words[1 + *offset], i - (1 + *offset));
      struct passwd pwd, *tpwd;
      int buflen = 1000;
      char* buffer = __alloca (buflen);
      int result;

      while ((result = __getpwnam_r (user, &pwd, buffer, buflen, &tpwd)) != 0
             && errno == ERANGE)
        buffer = extend_alloca (buffer, buflen, buflen + 1000);

      if (result == 0 && tpwd != NULL && pwd.pw_dir)
        *word = w_addstr (*word, word_length, max_length, pwd.pw_dir);
      else
        {
          /* (invalid login name) */
          *word = w_addchar (*word, word_length, max_length, '~');
          if (*word != NULL)
            *word = w_addstr (*word, word_length, max_length, user);
        }

      *offset = i - 1;
    }
  return *word ? 0 : WRDE_NOSPACE;
}


static int
do_parse_glob (const char *glob_word, char **word, size_t *word_length,
               size_t *max_length, wordexp_t *pwordexp, const char *ifs,
               const char *ifs_white)
{
  int error;
  unsigned int match;
  glob_t globbuf;

  error = glob (glob_word, GLOB_NOCHECK, NULL, &globbuf);

  if (error != 0)
    {
      /* We can only run into memory problems.  */
      assert (error == GLOB_NOSPACE);
      return WRDE_NOSPACE;
    }

  if (ifs && !*ifs)
    {
      /* No field splitting allowed. */
      assert (globbuf.gl_pathv[0] != NULL);
      *word = w_addstr (*word, word_length, max_length, globbuf.gl_pathv[0]);
      for (match = 1; match < globbuf.gl_pathc && *word != NULL; ++match)
        {
          *word = w_addchar (*word, word_length, max_length, ' ');
          if (*word != NULL)
            *word = w_addstr (*word, word_length, max_length,
                              globbuf.gl_pathv[match]);
        }

      globfree (&globbuf);
      return *word ? 0 : WRDE_NOSPACE;
    }

  assert (ifs == NULL || *ifs != '\0');
  if (*word != NULL)
    {
      free (*word);
      *word = w_newword (word_length, max_length);
    }

  for (match = 0; match < globbuf.gl_pathc; ++match)
    {
      char *matching_word = __strdup (globbuf.gl_pathv[match]);
      if (matching_word == NULL || w_addword (pwordexp, matching_word))
        {
          globfree (&globbuf);
          return WRDE_NOSPACE;
        }
    }

  globfree (&globbuf);
  return 0;
}

static int
parse_glob (char **word, size_t *word_length, size_t *max_length,
            const char *words, size_t *offset, int flags,
            wordexp_t *pwordexp, const char *ifs, const char *ifs_white)
{
  /* We are poised just after a '*', a '[' or a '?'. */
  int error = WRDE_NOSPACE;
  int quoted = 0; /* 1 if singly-quoted, 2 if doubly */
  size_t i;
  wordexp_t glob_list; /* List of words to glob */

  glob_list.we_wordc = 0;
  glob_list.we_wordv = NULL;
  glob_list.we_offs = 0;
  for (; words[*offset] != '\0'; ++*offset)
    {
      if (strchr (ifs, words[*offset]) != NULL)
        /* Reached IFS */
        break;

      /* Sort out quoting */
      if (words[*offset] == '\'')
        {
          if (quoted == 0)
            {
              quoted = 1;
              continue;
            }
          else if (quoted == 1)
            {
              quoted = 0;
              continue;
            }
        }
      else if (words[*offset] == '"')
        {
          if (quoted == 0)
            {
              quoted = 2;
              continue;
            }
          else if (quoted == 2)
            {
              quoted = 0;
              continue;
            }
        }

      /* Sort out other special characters */
      if (quoted != 1 && words[*offset] == '$')
        {
          error = parse_dollars (word, word_length, max_length, words,
                                 offset, flags, &glob_list, ifs, ifs_white,
                                 quoted == 2);
          if (error)
            goto tidy_up;

          continue;
        }
      else if (words[*offset] == '\\')
        {
          if (quoted)
            error = parse_qtd_backslash (word, word_length, max_length,
                                         words, offset);
          else
            error = parse_backslash (word, word_length, max_length,
                                     words, offset);

          if (error)
            goto tidy_up;

          continue;
        }

      *word = w_addchar (*word, word_length, max_length, words[*offset]);
      if (*word == NULL)
        goto tidy_up;
    }

  /* Don't forget to re-parse the character we stopped at. */
  --*offset;

  /* Glob the words */
  error = w_addword (&glob_list, *word);
  *word = w_newword (word_length, max_length);
  for (i = 0; error == 0 && i < glob_list.we_wordc; i++)
    error = do_parse_glob (glob_list.we_wordv[i], word, word_length,
                           max_length, pwordexp, ifs, ifs_white);

  /* Now tidy up */
tidy_up:
  wordfree (&glob_list);
  return error;
}

static int
parse_squote (char **word, size_t *word_length, size_t *max_length,
              const char *words, size_t *offset)
{
  /* We are poised just after a single quote */
  for (; words[*offset]; ++(*offset))
    {
      if (words[*offset] != '\'')
        {
          *word = w_addchar (*word, word_length, max_length, words[*offset]);
          if (*word == NULL)
            return WRDE_NOSPACE;
        }
      else return 0;
    }

  /* Unterminated string */
  return WRDE_SYNTAX;
}

/* Functions to evaluate an arithmetic expression */
static int
eval_expr_val (char **expr, long int *result)
{
  char *digit;

  /* Skip white space */
  for (digit = *expr; digit && *digit && isspace (*digit); ++digit);

  if (*digit == '(')
    {
      /* Scan for closing paren */
      for (++digit; **expr && **expr != ')'; ++(*expr));

      /* Is there one? */
      if (!**expr)
        return WRDE_SYNTAX;

      *(*expr)++ = 0;

      if (eval_expr (digit, result))
        return WRDE_SYNTAX;

      return 0;
    }

  /* POSIX requires that decimal, octal, and hexadecimal constants are
     recognized.  Therefore we pass 0 as the third parameter to strtol.  */
  *result = strtol (digit, expr, 0);
  if (digit == *expr)
    return WRDE_SYNTAX;

  return 0;
}

static int
eval_expr_multdiv (char **expr, long int *result)
{
  long int arg;

  /* Read a Value */
  if (eval_expr_val (expr, result) != 0)
    return WRDE_SYNTAX;

  while (**expr)
    {
      /* Skip white space */
      for (; *expr && **expr && isspace (**expr); ++(*expr));

      if (**expr == '*')
        {
          ++(*expr);
          if (eval_expr_val (expr, &arg) != 0)
            return WRDE_SYNTAX;

          *result *= arg;
        }
      else if (**expr == '/')
        {
          ++(*expr);
          if (eval_expr_val (expr, &arg) != 0)
            return WRDE_SYNTAX;

          /* Division by zero or integer overflow.  */
          if (arg == 0 || (arg == -1 && *result == LONG_MIN))
            return WRDE_SYNTAX;

          *result /= arg;
        }
      else break;
    }

  return 0;
}

static int
eval_expr (char *expr, long int *result)
{
  long int arg;

  /* Read a Multdiv */
  if (eval_expr_multdiv (&expr, result) != 0)
    return WRDE_SYNTAX;

  while (*expr)
    {
      /* Skip white space */
      for (; expr && *expr && isspace (*expr); ++expr);

      if (*expr == '+')
        {
          ++expr;
          if (eval_expr_multdiv (&expr, &arg) != 0)
            return WRDE_SYNTAX;

          *result += arg;
        }
      else if (*expr == '-')
        {
          ++expr;
          if (eval_expr_multdiv (&expr, &arg) != 0)
            return WRDE_SYNTAX;

          *result -= arg;
        }
      else break;
    }

  return 0;
}

static int
parse_arith (char **word, size_t *word_length, size_t *max_length,
             const char *words, size_t *offset, int flags, int bracket)
{
  /* We are poised just after "$((" or "$[" */
  int error;
  int paren_depth = 1;
  size_t expr_length;
  size_t expr_maxlen;
  char *expr;

  expr = w_newword (&expr_length, &expr_maxlen);
  for (; words[*offset]; ++(*offset))
    {
      switch (words[*offset])
        {
        case '$':
          error = parse_dollars (&expr, &expr_length, &expr_maxlen,
                                 words, offset, flags, NULL, NULL, NULL, 1);
          /* The ``1'' here is to tell parse_dollars not to
           * split the fields.
           */
          if (error)
            {
              free (expr);
              return error;
            }
          break;

        case '`':
          (*offset)++;
          error = parse_backtick (&expr, &expr_length, &expr_maxlen,
                                  words, offset, flags, NULL, NULL, NULL);
          /* The first NULL here is to tell parse_backtick not to
           * split the fields.
           */
          if (error)
            {
              free (expr);
              return error;
            }
          break;

        case '\\':
          error = parse_qtd_backslash (&expr, &expr_length, &expr_maxlen,
                                       words, offset);
          if (error)
            {
              free (expr);
              return error;
            }
          /* I think that a backslash within an
           * arithmetic expansion is bound to
           * cause an error sooner or later anyway though.
           */
          break;

        case ')':
          if (--paren_depth == 0)
            {
              char result[21];        /* 21 = ceil(log10(2^64)) + 1 */
              long int numresult = 0;
              long long int convertme;

              if (bracket || words[1 + *offset] != ')')
                {
                  free (expr);
                  return WRDE_SYNTAX;
                }

              ++(*offset);

              /* Go - evaluate. */
              if (*expr && eval_expr (expr, &numresult) != 0)
                {
                  free (expr);
                  return WRDE_SYNTAX;
                }

              if (numresult < 0)
                {
                  convertme = -numresult;
                  *word = w_addchar (*word, word_length, max_length, '-');
                  if (!*word)
                    {
                      free (expr);
                      return WRDE_NOSPACE;
                    }
                }
              else
                convertme = numresult;

              result[20] = '\0';
              *word = w_addstr (*word, word_length, max_length,
                                _itoa (convertme, &result[20], 10, 0));
              free (expr);
              return *word ? 0 : WRDE_NOSPACE;
            }
          expr = w_addchar (expr, &expr_length, &expr_maxlen, words[*offset]);
          if (expr == NULL)
            return WRDE_NOSPACE;

          break;

        case ']':
          if (bracket && paren_depth == 1)
            {
              char result[21];        /* 21 = ceil(log10(2^64)) + 1 */
              long int numresult = 0;

              /* Go - evaluate. */
              if (*expr && eval_expr (expr, &numresult) != 0)
                {
                  free (expr);
                  return WRDE_SYNTAX;
                }

              result[20] = '\0';
              *word = w_addstr (*word, word_length, max_length,
                                _itoa_word (numresult, &result[20], 10, 0));
              free (expr);
              return *word ? 0 : WRDE_NOSPACE;
            }

          free (expr);
          return WRDE_SYNTAX;

        case '\n':
        case ';':
        case '{':
        case '}':
          free (expr);
          return WRDE_BADCHAR;

        case '(':
          ++paren_depth;
        default:
          expr = w_addchar (expr, &expr_length, &expr_maxlen, words[*offset]);
          if (expr == NULL)
            return WRDE_NOSPACE;
        }
    }

  /* Premature end */
  free (expr);
  return WRDE_SYNTAX;
}

/* Function called by child process in exec_comm() */
static inline void
__attribute__ ((always_inline))
exec_comm_child (char *comm, int *fildes, int showerr, int noexec)
{
  const char *args[4] = { _PATH_BSHELL, "-c", comm, NULL };

  /* Execute the command, or just check syntax? */
  if (noexec)
    args[1] = "-nc";

  /* Redirect output.  */
  if (__glibc_likely (fildes[1] != STDOUT_FILENO))
    {
      __dup2 (fildes[1], STDOUT_FILENO);
      __close (fildes[1]);
    }
  else
    /* Reset the close-on-exec flag (if necessary).  */
    __fcntl (fildes[1], F_SETFD, 0);

  /* Redirect stderr to /dev/null if we have to.  */
  if (showerr == 0)
    {
      struct stat64 st;
      int fd;
      __close (STDERR_FILENO);
      fd = __open (_PATH_DEVNULL, O_WRONLY);
      if (fd >= 0 && fd != STDERR_FILENO)
        {
          __dup2 (fd, STDERR_FILENO);
          __close (fd);
        }
      /* Be paranoid.  Check that we actually opened the /dev/null
         device.  */
      if (__builtin_expect (__fxstat64 (_STAT_VER, STDERR_FILENO, &st), 0) != 0
          || __builtin_expect (S_ISCHR (st.st_mode), 1) == 0
#if defined DEV_NULL_MAJOR && defined DEV_NULL_MINOR
          || st.st_rdev != makedev (DEV_NULL_MAJOR, DEV_NULL_MINOR)
#endif
          )
        /* It's not the /dev/null device.  Stop right here.  The
           problem is: how do we stop?  We use _exit() with an
           hopefully unusual exit code.  */
        _exit (90);
    }

  /* Make sure the subshell doesn't field-split on our behalf. */
  __unsetenv ("IFS");

  __close (fildes[0]);
  __execve (_PATH_BSHELL, (char *const *) args, __environ);

  /* Bad.  What now?  */
  abort ();
}

/* Function to execute a command and retrieve the results */
/* pwordexp contains NULL if field-splitting is forbidden */
static int
exec_comm (char *comm, char **word, size_t *word_length, size_t *max_length,
           int flags, wordexp_t *pwordexp, const char *ifs,
           const char *ifs_white)
{
  int fildes[2];
#define bufsize 128
  int buflen;
  int i;
  int status = 0;
  size_t maxnewlines = 0;
  char buffer[bufsize];
  pid_t pid;
  int noexec = 0;

  /* Do nothing if command substitution should not succeed.  */
  if (flags & WRDE_NOCMD)
    return WRDE_CMDSUB;

  /* Don't fork() unless necessary */
  if (!comm || !*comm)
    return 0;

  if (__pipe2 (fildes, O_CLOEXEC) < 0)
    return WRDE_NOSPACE;

 again:
  if ((pid = __fork ()) < 0)
    {
      /* Bad */
      __close (fildes[0]);
      __close (fildes[1]);
      return WRDE_NOSPACE;
    }

  if (pid == 0)
    exec_comm_child (comm, fildes, noexec ? 0 : flags & WRDE_SHOWERR, noexec);

  /* Parent */

  /* If we are just testing the syntax, only wait.  */
  if (noexec)
    return (TEMP_FAILURE_RETRY (__waitpid (pid, &status, 0)) == pid
            && status != 0) ? WRDE_SYNTAX : 0;

  __close (fildes[1]);
  fildes[1] = -1;

  if (!pwordexp)
    /* Quoted - no field splitting */
    {
      while (1)
        {
          if ((buflen = TEMP_FAILURE_RETRY (__read (fildes[0], buffer,
                                                    bufsize))) < 1)
            {
              /* If read returned 0 then the process has closed its
                 stdout.  Don't use WNOHANG in that case to avoid busy
                 looping until the process eventually exits.  */
              if (TEMP_FAILURE_RETRY (__waitpid (pid, &status,
                                                 buflen == 0 ? 0 : WNOHANG))
                  == 0)
                continue;
              if ((buflen = TEMP_FAILURE_RETRY (__read (fildes[0], buffer,
                                                        bufsize))) < 1)
                break;
            }

          maxnewlines += buflen;

          *word = w_addmem (*word, word_length, max_length, buffer, buflen);
          if (*word == NULL)
            goto no_space;
        }
    }
  else
    /* Not quoted - split fields */
    {
      int copying = 0;
      /* 'copying' is:
       *  0 when searching for first character in a field not IFS white space
       *  1 when copying the text of a field
       *  2 when searching for possible non-whitespace IFS
       *  3 when searching for non-newline after copying field
       */

      while (1)
        {
          if ((buflen = TEMP_FAILURE_RETRY (__read (fildes[0], buffer,
                                                    bufsize))) < 1)
            {
              /* If read returned 0 then the process has closed its
                 stdout.  Don't use WNOHANG in that case to avoid busy
                 looping until the process eventually exits.  */
              if (TEMP_FAILURE_RETRY (__waitpid (pid, &status,
                                                 buflen == 0 ? 0 : WNOHANG))
                  == 0)
                continue;
              if ((buflen = TEMP_FAILURE_RETRY (__read (fildes[0], buffer,
                                                        bufsize))) < 1)
                break;
            }

          for (i = 0; i < buflen; ++i)
            {
              if (strchr (ifs, buffer[i]) != NULL)
                {
                  /* Current character is IFS */
                  if (strchr (ifs_white, buffer[i]) == NULL)
                    {
                      /* Current character is IFS but not whitespace */
                      if (copying == 2)
                        {
                          /*            current character
                           *                   |
                           *                   V
                           * eg: text<space><comma><space>moretext
                           *
                           * So, strip whitespace IFS (like at the start)
                           */
                          copying = 0;
                          continue;
                        }

                      copying = 0;
                      /* fall through and delimit field.. */
                    }
                  else
                    {
                      if (buffer[i] == '\n')
                        {
                          /* Current character is (IFS) newline */

                          /* If copying a field, this is the end of it,
                             but maybe all that's left is trailing newlines.
                             So start searching for a non-newline. */
                          if (copying == 1)
                            copying = 3;

	                          continue;
	                        }
	                      else
	                        {
	                          /* Current character is IFS white space, but
	                             not a newline */
	
	                          /* If not either copying a field or searching
	                             for non-newline after a field, ignore it */
	                          if (copying != 1 && copying != 3)
	                            continue;
	
	                          /* End of field (search for non-ws IFS afterwards) */
	                          copying = 2;
	                        }
	                    }
	
	                  /* First IFS white space (non-newline), or IFS non-whitespace.
	                   * Delimit the field.  Nulls are converted by w_addword. */
	                  if (w_addword (pwordexp, *word) == WRDE_NOSPACE)
	                    goto no_space;
	
	                  *word = w_newword (word_length, max_length);
	
	                  maxnewlines = 0;
	                  /* fall back round the loop.. */
	                }
	              else
	                {
	                  /* Not IFS character */
	
	                  if (copying == 3)
	                    {
	                      /* Nothing but (IFS) newlines since the last field,
	                         so delimit it here before starting new word */
	                      if (w_addword (pwordexp, *word) == WRDE_NOSPACE)
	                        goto no_space;
	
	                      *word = w_newword (word_length, max_length);
	                    }
	
	                  copying = 1;
	
	                  if (buffer[i] == '\n') /* happens if newline not in IFS */
	                    maxnewlines++;
	                  else
	                    maxnewlines = 0;
	
	                  *word = w_addchar (*word, word_length, max_length,
	                                     buffer[i]);
	                  if (*word == NULL)
	                    goto no_space;
	                }
	            }
	        }
	    }
	
	  /* Chop off trailing newlines (required by POSIX.2)  */
	  /* Ensure we don't go back further than the beginning of the
	     substitution (i.e. remove maxnewlines bytes at most) */
	  while (maxnewlines-- != 0 &&
	         *word_length > 0 && (*word)[*word_length - 1] == '\n')
	    {
	      (*word)[--*word_length] = '\0';
	
	      /* If the last word was entirely newlines, turn it into a new word
	       * which can be ignored if there's nothing following it. */
	      if (*word_length == 0)
	        {
	          free (*word);
	          *word = w_newword (word_length, max_length);
	          break;
	        }
	    }
	
	  __close (fildes[0]);
	  fildes[0] = -1;
	
	  /* Check for syntax error (re-execute but with "-n" flag) */
	  if (buflen < 1 && status != 0)
	    {
	      noexec = 1;
	      goto again;
	    }
	
	  return 0;
	
	no_space:
	  __kill (pid, SIGKILL);
	  TEMP_FAILURE_RETRY (__waitpid (pid, NULL, 0));
	  __close (fildes[0]);
	  return WRDE_NOSPACE;
	}
	
	static int
	parse_comm (char **word, size_t *word_length, size_t *max_length,
	            const char *words, size_t *offset, int flags, wordexp_t *pwordexp,
	            const char *ifs, const char *ifs_white)
	{
	  /* We are poised just after "$(" */
	  int paren_depth = 1;
	  int error = 0;
	  int quoted = 0; /* 1 for singly-quoted, 2 for doubly-quoted */
	  size_t comm_length;
	  size_t comm_maxlen;
	  t_word comm;
	  w_newword (&comm);
	  for (; words[*offset]; ++(*offset))
	    {
	      switch (words[*offset])
	        {
	        case '\'':
	          if (quoted == 0)
	            quoted = 1;
	          else if (quoted == 1)
	            quoted = 0;
	
	          break;
	
	        case '"':
	          if (quoted == 0)
	            quoted = 2;
	          else if (quoted == 2)
	            quoted = 0;
	
	          break;
	
	        case ')':
	          if (!quoted && --paren_depth == 0)
	            {
	              /* Go -- give script to the shell */
	              if (comm)
	                {
	#ifdef __libc_ptf_call
	                  /* We do not want the exec_comm call to be cut short
	                     by a thread cancellation since cleanup is very
	                     ugly.  Therefore disable cancellation for
	                     now.  */
	                  // XXX Ideally we do want the thread being cancelable.
	                  // XXX If demand is there we'll change it.
	                  int state = PTHREAD_CANCEL_ENABLE;
	                  __libc_ptf_call (__pthread_setcancelstate,
	                                   (PTHREAD_CANCEL_DISABLE, &state), 0);
	#endif
	
	                  error = exec_comm (comm, word, word_length, max_length,
	                                     flags, pwordexp, ifs, ifs_white);
	
	#ifdef __libc_ptf_call
	                  __libc_ptf_call (__pthread_setcancelstate,
	                                   (state, NULL), 0);
	#endif
	
	                  free (comm);
	                }
	
	              return error;
	            }
	
	          /* This is just part of the script */
	          break;
	
	        case '(':
	          if (!quoted)
	            ++paren_depth;
	        }
	
	      w_addchar (comm, words[*offset]);
	      if (comm == NULL)
	        return WRDE_NOSPACE;
	    }
	
	  /* Premature end.  */
	  free (comm);
	
	  return WRDE_SYNTAX;
	}
	
	#define CHAR_IN_SET(ch, char_set) \
	  (memchr (char_set "", ch, sizeof (char_set) - 1) != NULL)
	
	static int
	parse_backtick (char **word, size_t *word_length, size_t *max_length,
	                const char *words, size_t *offset, int flags,
	                wordexp_t *pwordexp, const char *ifs, const char *ifs_white)
	{
	  /* We are poised just after "`" */
	  int error;
	  int squoting = 0;
	  size_t comm_length;
	  size_t comm_maxlen;
	  char *comm = w_newword (&comm_length, &comm_maxlen);
	
	  for (; words[*offset]; ++(*offset))
	    {
	      switch (words[*offset])
	        {
	        case '`':
	          /* Go -- give the script to the shell */
	          error = exec_comm (comm, word, word_length, max_length, flags,
	                             pwordexp, ifs, ifs_white);
	          free (comm);
	          return error;
	
	        case '\\':
	          if (squoting)
	            {
	              error = parse_qtd_backslash (&comm, &comm_length, &comm_maxlen,
	                                           words, offset);
	
	              if (error)
	                {
	                  free (comm);
	                  return error;
	                }
	
	              break;
	            }
	
	          error = parse_backslash (&comm, &comm_length, &comm_maxlen, words,
	                                   offset);
	
	          if (error)
	            {
	              free (comm);
	              return error;
	            }
	
	          break;
	
	        case '\'':
	          squoting = 1 - squoting;
	        default:
	          comm = w_addchar (comm, &comm_length, &comm_maxlen, words[*offset]);
	          if (comm == NULL)
	            return WRDE_NOSPACE;
	        }
	    }
	
	  /* Premature end */
	  free (comm);
	  return WRDE_SYNTAX;
	}
	
	static int
	parse_dquote (char **word, size_t *word_length, size_t *max_length,
	              const char *words, size_t *offset, int flags,
	              wordexp_t *pwordexp, const char * ifs, const char * ifs_white)
	{
	  /* We are poised just after a double-quote */
	  int error;
	
	  for (; words[*offset]; ++(*offset))
	    {
	      switch (words[*offset])
	        {
	        case '"':
	          return 0;
	
	        case '$':
	          error = parse_dollars (word, word_length, max_length, words, offset,
	                                 flags, pwordexp, ifs, ifs_white, 1);
	          /* The ``1'' here is to tell parse_dollars not to
	           * split the fields.  It may need to, however ("$@").
	           */
	          if (error)
	            return error;
	
	          break;
	
	        case '`':
	          ++(*offset);
	          error = parse_backtick (word, word_length, max_length, words,
	                                  offset, flags, NULL, NULL, NULL);
	          /* The first NULL here is to tell parse_backtick not to
	           * split the fields.
	           */
	          if (error)
	            return error;
	
	          break;
	
	        case '\\':
	          error = parse_qtd_backslash (word, word_length, max_length, words,
	                                       offset);
	
	          if (error)
	            return error;
	
	          break;
	
	        default:
	          *word = w_addchar (*word, word_length, max_length, words[*offset]);
	          if (*word == NULL)
	            return WRDE_NOSPACE;
	        }
	    }
	
	  /* Unterminated string */
	  return WRDE_SYNTAX;
	}
	
	/*
	 * wordfree() is to be called after pwordexp is finished with.
	 */
	
	void
	wordfree (wordexp_t *pwordexp)
	{
	
	  /* wordexp can set pwordexp to NULL */
	  if (pwordexp && pwordexp->we_wordv)
	    {
	      char **wordv = pwordexp->we_wordv;
	
	      for (wordv += pwordexp->we_offs; *wordv; ++wordv)
	        free (*wordv);
	
	      free (pwordexp->we_wordv);
	      pwordexp->we_wordv = NULL;
	    }
	}
	libc_hidden_def (wordfree)
	
	/*
	 * wordexp()
	 */
	
	int
	wordexp (const char *words, wordexp_t *pwordexp, int flags)
	{
	  size_t words_offset;
	  size_t word_length;
	  size_t max_length;
	  char *word = w_newword (&word_length, &max_length);
	  int error;
	  char *ifs;
	  char ifs_white[4];
	  wordexp_t old_word = *pwordexp;
	
	  if (flags & WRDE_REUSE)
	    {
	      /* Minimal implementation of WRDE_REUSE for now */
	      wordfree (pwordexp);
	      old_word.we_wordv = NULL;
	    }
	
	  if ((flags & WRDE_APPEND) == 0)
	    {
	      pwordexp->we_wordc = 0;
	
	      if (flags & WRDE_DOOFFS)
	        {
	          pwordexp->we_wordv = calloc (1 + pwordexp->we_offs, sizeof (char *));
	          if (pwordexp->we_wordv == NULL)
	            {
	              error = WRDE_NOSPACE;
	              goto do_error;
	            }
	        }
	      else
	        {
	          pwordexp->we_wordv = calloc (1, sizeof (char *));
	          if (pwordexp->we_wordv == NULL)
	            {
	              error = WRDE_NOSPACE;
	              goto do_error;
	            }
	
	          pwordexp->we_offs = 0;
	        }
	    }
	
	  /* Find out what the field separators are.
	   * There are two types: whitespace and non-whitespace.
	   */
	  ifs = getenv ("IFS");
	
	  if (ifs == NULL)
	    /* IFS unset - use <space><tab><newline>. */
	    ifs = strcpy (ifs_white, " \t\n");
	  else
	    {
	      char *ifsch = ifs;
	      char *whch = ifs_white;
	
	      while (*ifsch != '\0')
	        {
	          if (*ifsch == ' ' || *ifsch == '\t' || *ifsch == '\n')
	            {
	              /* Whitespace IFS.  See first whether it is already in our
	                 collection.  */
	              char *runp = ifs_white;
	
	              while (runp < whch && *runp != *ifsch)
	                ++runp;
	
	              if (runp == whch)
	                *whch++ = *ifsch;
	            }
	
	          ++ifsch;
	        }
	      *whch = '\0';
	    }
	
	  for (words_offset = 0 ; words[words_offset] ; ++words_offset)
	    switch (words[words_offset])
	      {
	      case '\\':
	        error = parse_backslash (&word, &word_length, &max_length, words,
	                                 &words_offset);
	
	        if (error)
	          goto do_error;
	
	        break;
	
	      case '$':
	        error = parse_dollars (&word, &word_length, &max_length, words,
	                               &words_offset, flags, pwordexp, ifs, ifs_white,
	                               0);
	
	        if (error)
	          goto do_error;
	
	        break;
	
	      case '`':
	        ++words_offset;
	        error = parse_backtick (&word, &word_length, &max_length, words,
	                                &words_offset, flags, pwordexp, ifs,
	                                ifs_white);
	
	        if (error)
	          goto do_error;
	
	        break;
	
	      case '"':
	        ++words_offset;
	        error = parse_dquote (&word, &word_length, &max_length, words,
	                              &words_offset, flags, pwordexp, ifs, ifs_white);
	
	        if (error)
	          goto do_error;
	
	        if (!word_length)
	          {
	            error = w_addword (pwordexp, NULL);
	
	            if (error)
	              return error;
	          }
	
	        break;
	
	      case '\'':
	        ++words_offset;
	        error = parse_squote (&word, &word_length, &max_length, words,
	                              &words_offset);
	
	        if (error)
	          goto do_error;
	
	        if (!word_length)
	          {
	            error = w_addword (pwordexp, NULL);
	
	            if (error)
	              return error;
	          }
	
	        break;
	
	      case '~':
	        error = parse_tilde (&word, &word_length, &max_length, words,
	                             &words_offset, pwordexp->we_wordc);
	
	        if (error)
	          goto do_error;
	
	        break;
	
	      case '*':
	      case '[':
	      case '?':
	        error = parse_glob (&word, &word_length, &max_length, words,
	                            &words_offset, flags, pwordexp, ifs, ifs_white);
	
	        if (error)
	          goto do_error;
	
	        break;
	
	      default:
	        /* Is it a word separator? */
	        if (strchr (" \t", words[words_offset]) == NULL)
	          {
	            char ch = words[words_offset];
	
	            /* Not a word separator -- but is it a valid word char? */
	            if (strchr ("\n|&;<>(){}", ch))
	              {
	                /* Fail */
	                error = WRDE_BADCHAR;
	                goto do_error;
	              }
	
	            /* "Ordinary" character -- add it to word */
	            word = w_addchar (word, &word_length, &max_length,
	                              ch);
	            if (word == NULL)
	              {
	                error = WRDE_NOSPACE;
	                goto do_error;
	              }
	
	            break;
	          }
	
	        /* If a word has been delimited, add it to the list. */
	        if (word != NULL)
	          {
	            error = w_addword (pwordexp, word);
	            if (error)
	              goto do_error;
	          }
	
	        word = w_newword (&word_length, &max_length);
	      }
	
	  /* End of string */
	
	  /* There was a word separator at the end */
	  if (word == NULL) /* i.e. w_newword */
	    return 0;
	
	  /* There was no field separator at the end */
	  return w_addword (pwordexp, word);
	
	do_error:
	  /* Error:
	   *        free memory used (unless error is WRDE_NOSPACE), and
	   *        set pwordexp members back to what they were.
	   */
	
	  free (word);
	
	  if (error == WRDE_NOSPACE)
	    return WRDE_NOSPACE;
	
	  if ((flags & WRDE_APPEND) == 0)
	    wordfree (pwordexp);
	
	  *pwordexp = old_word;
	  return error;
	}
	
