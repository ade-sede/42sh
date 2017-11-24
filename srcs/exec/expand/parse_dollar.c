#include <stdio.h>
#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "t_env.h"
#include "local.h"
#include "exec.h"
#include "glob.h"
#include "expand.h"

static int		is_arith_expansion(t_expand *exp)
{
	int			i;
	int			depth;

	depth = 0;
	i = 3 + exp->offset;
	while (exp->words[i] && !(depth == 0 && exp->words[i] == ')'))
	{
		if (exp->words[i] == '(')
			++depth;
		else if (exp->words[i] == ')')
			--depth;
		++i;
	}
	if (exp->words[i] == ')' && exp->words[i + 1] == ')')
	{
		return (1);
	}
	return (0);
}

int				parse_dollars(t_expand *exp, int quoted)
{
	if (exp->words[1 + exp->offset] == '"' ||
	exp->words[1 + exp->offset] == '\\' || exp->words[1 + exp->offset] == '\0')
	{
		w_addchar(&exp->word, '$');
		return (0);
	}
	if (exp->words[1 + exp->offset] == '(')
	{
		if (exp->words[2 + exp->offset] == '(')
		{
			if (is_arith_expansion(exp))
			{
				(exp->offset) += 3;
				return (parse_arith(exp));
			}
		}
		(exp->offset) += 2;
		return (parse_comm(exp, quoted));
	}
	else
	{
		++(exp->offset);
		return (parse_param(exp, quoted));
	}
}
