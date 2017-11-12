#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "env.h"
#include "exec.h"
#include "glob.h"
#include "expand.h"

int		parse_backslash (t_word *g_word, t_word *word, const char *words, size_t *offset)
{
	char	ch;

	ch = words[1 + *offset];
	if (ch == 0)
		return WRDE_SYNTAX;
	else
	{
		w_addchar (word, words[1 + *offset]);
		w_addchar (g_word, words[*offset]);
		w_addchar (g_word, words[1 + *offset]);
		++(*offset);
	}
	return 0;
}

int		parse_qtd_backslash (t_word *g_word, t_word *word, const char *words, size_t *offset)
{
	if (words[1 + *offset] == 0)
		return WRDE_SYNTAX;
	w_addchar (g_word, '\\');
	if (ft_strchr("*[?", words[1 + *offset]))
		w_addchar (g_word, '\\');
	if (ft_strchr("$`\"\\", words[1 + *offset]) != NULL)
	{
		w_addchar (word, words[1 + *offset]);
		w_addchar (g_word, words[1 + *offset]);
		++(*offset);
	}
	else
	{
		w_addchar (word, words[*offset]);
		w_addchar (word, words[1 + *offset]);
		w_addchar (g_word, words[*offset]);
		w_addchar (g_word, words[1 + *offset]);
		++(*offset);
	}
	return 0;
}

int		parse_squote (t_word *g_word, t_word *word, const char *words, size_t *offset)
{
	while (words[*offset])
	{
		if (words[*offset] == '\'')
			return 0;
		/* backlash des caracteres de globing dans les quotes */
		if (ft_strchr("*[?\\", words[*offset]))
		{
			w_addchar (g_word, '\\');
			w_addchar (g_word, words[*offset]); 
		}
		else
			w_addchar (g_word, words[*offset]);
		w_addchar (word, words[*offset]);
		++(*offset);
	}
	return WRDE_SYNTAX;
}

int		parse_dquote (t_word *g_word, t_word *word,
		const char *words, size_t *offset,
		t_expand *exp, const char *ifs)
{
	while (words[*offset])
	{
		if (words[*offset] == '"')
			return 0;
		else if (words[*offset] == '\\')
			parse_qtd_backslash (g_word, word, words, offset);
		/*		else if (words[*offset] == '$')
				parse_dollars (word, word_length, max_length, words, offset,
				flags, pwordexp, ifs, ifs_white, 1);
				else if (words[*offset] == '`')
				{
				++(*offset);
				error = parse_backtick (word, word_length, max_length, words,
				offset, flags, NULL, NULL, NULL);
				}
				*/
		else if (ft_strchr("*[?", words[*offset]))
		{
			w_addchar (g_word, '\\');
			w_addchar (g_word, words[*offset]); 
			w_addchar (word, words[*offset]);
		}
		else
		{
			w_addchar (g_word, words[*offset]);
			w_addchar (word, words[*offset]);
		}
		++(*offset);
	}
	return (WRDE_SYNTAX);
}

int parse_tilde (t_word *g_word, t_word *word,
             const char *words, size_t *offset)
{
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

char	**wordexp (const char *words)
{
	size_t	offset;
	t_word	word;
	t_word	g_word;
	int error;
	char *ifs;
	t_expand exp;

	w_newword (&word);
	w_newword (&g_word);
	w_newexp (&exp);

	ifs = getenv ("IFS");

	if (ifs == NULL)
		ifs = ft_strdup(" \t\n");

	offset = 0;
	while (words[offset])
	{
		if (words[offset] == '\\')
			parse_backslash (&g_word, &word, words, &offset);
		else if (words[offset] == '"')
		{
			++offset;
			parse_dquote (&g_word, &word, words, &offset, &exp, ifs);
			if (!word.str && !words[1 + offset])
				w_addword (&exp, &g_word, &word);
		}
		else if (words[offset] == '\'')
		{
			++offset;
			parse_squote (&g_word, &word, words, &offset);
			if (!word.str && !words[1 + offset])
				w_addword (&exp, &g_word, &word);
		}
		/*
		   else if (words[offset] == '`')
		   {
		   ++offset;
		   parse_backtick (&word, &word_length, &max_length, words,
		   &offset, flags, pwordexp, ifs);
		   }
		   */
		   else if (words[offset] == '$')
			   parse_dollars (&g_word, &word, words, &offset, &exp, ifs, 0);
		   else if (words[offset] == '~')
			   parse_tilde (&g_word, &word, words, &offset);
		else
		{
//			printf("w: {%s}, gw: {%s}\nwsize: {%zu}, gwsize: {%zu}\n", word.str, g_word.str, word.actlen, g_word.actlen);
//			printf("wsize max: {%zu}, gwsize max: {%zu}\n", word.maxlen, g_word.maxlen);
			w_addchar (&word, words[offset]);
			w_addchar (&g_word, words[offset]);
		}
		offset++;
	}
	if (word.str != NULL)
		w_addword (&exp, &g_word, &word);
	int	i;
	for (i=0; i < exp.actlen; i++)
	{
		printf("w: {%s}, gw: {%s}\n", exp.av_word[i], exp.av_gword[i]);
	}
	return (exp.av_word);
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("bad ac\n");
		return (1);
	}
	wordexp(av[1]);
	return (0);
}
