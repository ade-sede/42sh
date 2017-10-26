#include "exec.h"
/*
**	complete_command : list separator_op
**	                 | list
*/

int exec_complete_command(t_ast *ast)
{
	if (ast->child[0])
		return (exec(ast->child[0]));
}
