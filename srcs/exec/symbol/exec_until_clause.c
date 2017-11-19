#include "exec.h"

/*
** until_clause     : Until compound_list do_group
*/

int exec_until_clause(t_ast *ast) 
{
	while (exec(ast->child[1]) == EXIT_FAILURE)
		exec(ast->child[2]);
	return (EXIT_SUCCESS);
}
