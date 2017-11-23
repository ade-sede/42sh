#include "exec.h"

/*
**					  0       1             2        3         4
**	else_part        : Elif compound_list Then compound_list
**	                 | Elif compound_list Then compound_list else_part
**	                 | Else compound_list
*/

int		exec_else_part(t_ast *ast)
{
	if (is_token(ast->child[0], TK_ELIF))
	{
		if (exec(ast->child[1]) == EXIT_SUCCESS)
			return (exec(ast->child[3]));
		else if (ast->child[4])
			return (exec(ast->child[4]));
		return (EXIT_FAILURE);
	}
	else
		return (exec(ast->child[1]));
}
