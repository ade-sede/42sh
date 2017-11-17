#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "t_env.h"
#include "exec.h"
#include "glob.h"
#include "expand.h"

/*  on \ */
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

/*  on \ */
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

/*  after ' */
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

/*  after " */
int		parse_dquote (t_expand *exp)
{
	while (exp->words[exp->offset])
	{
		if (exp->words[exp->offset] == '"')
			return 0;
		else if (exp->words[exp->offset] == '\\')
			parse_qtd_backslash (&exp->g_word, &exp->word, exp->words, &exp->offset);
		else if (exp->words[exp->offset] == '$')
		{
			exp->quoted = 1;
			parse_dollars (exp);
			exp->quoted = 0;
		}
		else if (exp->words[exp->offset] == '`')
		{
			++(exp->offset);
			parse_backtick (exp);
		}
		else if (ft_strchr("*[?", exp->words[exp->offset]))
		{
			w_addchar (&exp->g_word, '\\');
			w_addchar (&exp->g_word, exp->words[exp->offset]); 
			w_addchar (&exp->word, exp->words[exp->offset]);
		}
		else
		{
			w_addchar (&exp->g_word, exp->words[exp->offset]);
			w_addchar (&exp->word, exp->words[exp->offset]);
		}
		++(exp->offset);
	}
	return (WRDE_SYNTAX);
}
