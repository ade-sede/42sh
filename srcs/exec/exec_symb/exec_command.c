#include "exec.h"

/*
**	command          : simple_command
**	                 | compound_command
**	                 | compound_command redirect_list
**	                 | function_definition
*/

int exec_command(t_ast *ast)
{
	int		exit_status;
	t_list	*redirect_list = NULL;

	if (ast->child[1])
	{
		exec_redirect_list(ast->child[1], &redirect_list);
		exec_dup(redirect_list);
	}
	exit_status = exec(ast->child[0]);
	if (ast->child[1])
		close_dup(redirect_list);
	return (exit_status);
}
