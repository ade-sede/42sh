#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "t_env.h"
#include "exec.h"
#include "glob.h"
#include "expand.h"

/*  after "`" */
int		parse_backtick (t_expand *exp)
{
	t_word comm;
	w_newword (&comm);

	while (exp->words[exp->offset])
	{
		if (exp->words[exp->offset] == '`')
		{
			exec_comm (comm.str, exp);
			return 0;
		}
		else
			w_addchar (&comm, exp->words[exp->offset]);
		++(exp->offset);
	}
	w_free (&comm);
	return WRDE_SYNTAX;
}
