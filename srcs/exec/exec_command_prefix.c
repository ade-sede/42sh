#include "exec.h"
#include "hash_table.h"
#include "expand.h"
#include "builtin.h"
#include "failure.h"
#include "local.h"
#include "job_control.h"

/*
**	cmd_prefix       :            io_redirect
**	                 | cmd_prefix io_redirect
**	                 |            ASSIGNMENT_WORD
**	                 | cmd_prefix ASSIGNMENT_WORD
**	                 ;
*/

void	exec_assignment_word(t_ast *ast)
{
	char		**word_expanded;
	char		*eq_pos;

	word_expanded = NULL;
	eq_pos = ft_strchr(ast->token->value, '=');
	word_expanded = word_expansion(eq_pos + 1, NO_GLOBBING | NO_FIELDSPLITING);
	if (word_expanded[0])
	{
		*eq_pos = 0;
		local_add_change_from_key_value(singleton_env(), ast->token->value, \
				word_expanded[0]);
		*eq_pos = '=';
	}
	else
		local_add_change_from_string(singleton_env(), ast->token->value);
	ft_arraydel(&word_expanded);
}

int		exec_cmd_prefix(t_ast *ast, t_list **redirect_list)
{
	t_ast	*assignement_word;
	t_ast	*io_redirect;

	assignement_word = NULL;
	io_redirect = NULL;
	if (is_symb(ast->child[0], IO_REDIRECT))
		io_redirect = ast->child[0];
	else if (is_symb(ast->child[1], IO_REDIRECT))
		io_redirect = ast->child[1];
	if (is_token(ast->child[0], TK_ASSIGNMENT_WORD))
		assignement_word = ast->child[0];
	else if (is_token(ast->child[1], TK_ASSIGNMENT_WORD))
		assignement_word = ast->child[1];
	if (assignement_word)
		exec_assignment_word(assignement_word);
	if (io_redirect)
		if (!(exec_io_redirect(io_redirect, redirect_list)))
			return (0);
	if (is_symb(ast->child[0], CMD_PREFIX))
		return (exec_cmd_prefix(ast->child[0], redirect_list));
	return (1);
}
