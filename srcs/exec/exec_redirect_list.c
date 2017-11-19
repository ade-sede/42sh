#include "exec.h"

/*
** redirect_list    :               io_redirect
**                  | redirect_list io_redirect
*/

void	exec_redirect_list(t_ast *ast, t_list **redirect_list)
{
	t_ast	*io_redirect;

	io_redirect = ast->child[1] ? ast->child[1] : ast->child[0];
	exec_io_redirect(io_redirect, redirect_list);
	if (ast->child[1])
		exec_redirect_list(ast->child[0], redirect_list);
}
