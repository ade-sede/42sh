#include "exec.h"
/*
**	complete_command : list separator_op
**	                 | list
*/

int exec_complete_command(t_ast *ast)
{
	return (exec(ast->child[0]));
}
