#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "t_env.h"
#include "exec.h"
#include "glob.h"
#include "expand.h"

int		parse_backslash(t_word *g_word, t_word *word, const char *words,
				size_t *offset)
{
	char	ch;

	ch = words[1 + *offset];
	if (ch == 0)
		return (WRDE_SYNTAX);
	else
	{
		w_addchar(word, words[1 + *offset]);
		w_addchar(g_word, words[*offset]);
		w_addchar(g_word, words[1 + *offset]);
		++(*offset);
	}
	return (0);
}

int		parse_qtd_backslash(t_word *g_word, t_word *word, const char *words,
				size_t *offset)
{
	if (words[1 + *offset] == 0)
		return (WRDE_SYNTAX);
	w_addchar(g_word, '\\');
	if (ft_strchr("*[?", words[1 + *offset]))
		w_addchar(g_word, '\\');
	if (ft_strchr("$`\"\\", words[1 + *offset]) != NULL)
	{
		w_addchar(word, words[1 + *offset]);
		w_addchar(g_word, words[1 + *offset]);
		++(*offset);
	}
	else
	{
		w_addchar(word, words[*offset]);
		w_addchar(word, words[1 + *offset]);
		w_addchar(g_word, words[*offset]);
		w_addchar(g_word, words[1 + *offset]);
		++(*offset);
	}
	return (0);
}

int		parse_squote(t_word *g_word, t_word *word, const char *words,
				size_t *offset)
{
	while (words[*offset])
	{
		if (words[*offset] == '\'')
			return (0);
		if (ft_strchr("*[?\\", words[*offset]))
		{
			w_addchar(g_word, '\\');
			w_addchar(g_word, words[*offset]);
		}
		else
			w_addchar(g_word, words[*offset]);
		w_addchar(word, words[*offset]);
		++(*offset);
	}
	return (WRDE_SYNTAX);
}

int		parse_dquote(t_expand *exp)
{
	while (exp->words[exp->offset])
	{
		if (exp->words[exp->offset] == '"')
			return (0);
		else if (exp->words[exp->offset] == '\\')
			parse_qtd_backslash(&exp->g_word, &exp->word, exp->words,
							&exp->offset);
		else if (exp->words[exp->offset] == '$')
			parse_dollars(exp, 1);
		else if (exp->words[exp->offset] == '`' && ++(exp->offset))
			parse_backtick(exp, 1);
		else if (ft_strchr("*[?", exp->words[exp->offset]))
		{
			w_addchar(&exp->g_word, '\\');
			w_addchar(&exp->g_word, exp->words[exp->offset]);
			w_addchar(&exp->word, exp->words[exp->offset]);
		}
		else
		{
			w_addchar(&exp->g_word, exp->words[exp->offset]);
			w_addchar(&exp->word, exp->words[exp->offset]);
		}
		++(exp->offset);
	}
	return (WRDE_SYNTAX);
}
