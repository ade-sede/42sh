#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "env.h"
#include "exec.h"
#include "glob.h"
#include "expand.h"

int parse_tilde (t_word *g_word, t_word *word,
             const char *words, size_t *offset)
{
	(void)words;
	(void)offset;
      char* home;

      home = getenv ("HOME");
      if (home != NULL)
	  {
          w_addstr (word, home);
          w_addstr (g_word, home);
	  }
      else
	  {
		  w_addchar (word, '~');
		  w_addchar (g_word, '~');
	  }
	  return (1);
}
