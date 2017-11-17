#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "t_env.h"
#include "exec.h"
#include "glob.h"
#include "expand.h"
#include <stdio.h>

/*  after "$(" */

int		parse_comm (t_expand *exp)
{
	int paren_depth = 1;
	int quoted = 0;
	int error = 0;
	t_word comm;

	w_newword (&comm);
	while (exp->words[exp->offset])
	{
		if (exp->words[exp->offset] == '\'')
		{
			if (quoted == 0)
				quoted = 1;
			else if (quoted == 1)
				quoted = 0;
		}
		if (exp->words[exp->offset] == '"')
		{
			if (quoted == 0)
				quoted = 2;
			else if (quoted == 2)
				quoted = 0;
		}
		if (exp->words[exp->offset] == ')')
		{
			if (!quoted && --paren_depth == 0)
			{
				if (comm.str)
				{
#ifdef EXPAND_DEBUG
 fprintf(stderr,"exec comm\n");
 #endif
					error = exec_comm (comm.str, exp);
					w_free (&comm);
					return error;
				}
			}
		}
		if (exp->words[exp->offset] == '(' && !quoted)
			++paren_depth;
		w_addchar (&comm, exp->words[exp->offset]);
		++exp->offset;
	}
	w_free (&comm);
	return WRDE_SYNTAX;
}
