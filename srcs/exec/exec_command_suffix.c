#include "exec.h"
#include "hash_table.h"
#include "expand.h"
#include "builtin.h"
#include "failure.h"
#include "local.h"
#include "job_control.h"

/*
**	cmd_suffix       :            io_redirect
**	                 | cmd_suffix io_redirect
**	                 |            WORD
**	                 | cmd_suffix WORD
*/

int	exec_cmd_suffix(t_ast *ast, t_list **redirect_list, char ***av)
{
	t_ast	*io_redirect;
	t_ast	*word;
	char	**word_expanded;

	word = NULL;
	io_redirect = NULL;
	if (is_symb(ast->child[0], IO_REDIRECT))
		io_redirect = ast->child[0];
	else if (is_symb(ast->child[1], IO_REDIRECT))
		io_redirect = ast->child[1];
	if (is_token(ast->child[0], TK_WORD))
		word = ast->child[0];
	else if (is_token(ast->child[1], TK_WORD))
		word = ast->child[1];
	if (word)
	{
		word_expanded = word_expansion(word->token->value, 0);
		*av = *av ? ft_arrayjoin_free(word_expanded, *av, 0b11) : word_expanded;
	}
	if (io_redirect)
		if (!(exec_io_redirect(io_redirect, redirect_list)))
			return (0);
	if (is_symb(ast->child[0], CMD_SUFFIX))
		return (exec_cmd_suffix(ast->child[0], redirect_list, av));
	return (1);
}
