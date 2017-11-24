#include "exec.h"

/*
**	complete_commands: complete_commands newline_list complete_command
**	                 |                                complete_command
*/

int exec_complete_commands(t_ast *ast)
{
	if (ast->child[0] && !ast->child[2])
		return (exec(ast->child[0]));
	exec(ast->child[0]);
	return (exec(ast->child[2]));
}
