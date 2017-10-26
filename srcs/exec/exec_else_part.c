#include "exec.h"
/*
** else_part        : Elif compound_list Then else_part
**					| Else compound_list
*/

int exec_else_part(t_ast *ast)
{
	int		exit_status;

	if ((exit_status = exec(ast->child[1])) == EXIT_SUCCESS
		&& ast->child[2])
			exec_else_part(ast->child[3]);
	return (exit_status);
}
