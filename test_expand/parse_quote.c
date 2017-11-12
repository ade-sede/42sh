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
		else if (words[*offset] == '$')
			   parse_dollars (g_word, word, words, offset, exp, ifs, 1);
		/*
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
