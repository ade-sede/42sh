#include "exec.h"
/*
**	command          : simple_command
**	                 | compound_command
**	                 | compound_command redirect_list
**	                 | function_definition
*/

int exec_command(t_ast *ast)
{
	/*
**		if (ast->child[1])
**			exec_redirect_list();
*/
	return (exec(ast->child[0]));
}
