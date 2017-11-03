#include "exec.h"
/*
**	term             : term separator and_or
**	                 |                and_or
*/

int exec_term(t_ast *ast)
{
	if (ast->child[0] && !ast->child[2])
		return (exec(ast->child[0]));
	exec(ast->child[0]);
	return (exec(ast->child[2]));
}
