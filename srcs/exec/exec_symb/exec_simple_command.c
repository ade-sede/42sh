#include "exec.h"
#include "builtin.h"
#include "local.h"
#include "job_control.h"

/*
**	cmd_suffix       :            io_redirect
**	                 | cmd_suffix io_redirect
**	                 |            WORD
**	                 | cmd_suffix WORD
*/

void	exec_cmd_suffix(t_ast	*ast, t_list **redirect_list, char **av)
{
	t_ast	*io_redirect = NULL;
	t_ast	*word = NULL;

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
		*av = ft_strdup(word->token->value);
		av--;
	}
	if (io_redirect)
		exec_io_redirect(io_redirect, redirect_list);
	if (is_symb(ast->child[0], CMD_SUFFIX))
		exec_cmd_suffix(ast->child[0], redirect_list, av);
}

/*
**	cmd_prefix       :            io_redirect
**	                 | cmd_prefix io_redirect
**	                 |            ASSIGNMENT_WORD
**	                 | cmd_prefix ASSIGNMENT_WORD
**	                 ;
*/

void	exec_assignment_word(t_ast *ast)
{
	add_to_local(&singleton_env()->local, ft_strdup(ast->token->value));
}

void	exec_cmd_prefix(t_ast	*ast, t_list **redirect_list)
{
	t_ast	*assignement_word = NULL;
	t_ast	*io_redirect = NULL;

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
		exec_io_redirect(io_redirect, redirect_list);
	if (is_symb(ast->child[0], CMD_PREFIX))
		exec_cmd_prefix(ast->child[0], redirect_list);
}

char	*extract_word(t_ast *ast)
{
	return (ft_strdup(ast->token->value));
}

char	*get_cmd_name(t_ast	*ast)
{
	if (is_symb(ast->child[1], CMD_WORD))
		return (extract_word(ast->child[1]->child[0]));
	else if (is_symb(ast->child[0], CMD_NAME))
		return (extract_word(ast->child[0]->child[0]));
	return (NULL);
}

int		count_words(t_ast *ast)
{
	int	word;

	word = 0;
	if (is_token(ast->child[0], TK_WORD) || is_token(ast->child[1], TK_WORD))
		word = 1;
	if (is_symb(ast->child[0], CMD_SUFFIX))
		return (word + count_words(ast->child[0]));
	return (word);
}

/*
**	simple_command   : cmd_prefix cmd_word cmd_suffix
**	                 | cmd_prefix cmd_word
**	                 | cmd_prefix
**	                 | cmd_name cmd_suffix
**	                 | cmd_name
*/

int		exec_simple_command(t_ast *ast)
{
	char	**av;
	t_list	*redirect_list = NULL;
	t_ast	*cmd_suffix = NULL;
	t_ast	*fct_body = NULL;
	int		nb_word;

	av = ft_memalloc(sizeof(char *) * 4096);
	ft_bzero((void*)av, 4096 * 8);
	exec_cmd_prefix(ast, &redirect_list);
	if (is_symb(ast->child[0], CMD_PREFIX))
		exec_cmd_prefix(ast->child[0], &redirect_list);

	av[0] = get_cmd_name(ast);

	if (is_symb(ast->child[1], CMD_SUFFIX))
		cmd_suffix = ast->child[1];
	if (is_symb(ast->child[2], CMD_SUFFIX))
		cmd_suffix = ast->child[2];

	if (cmd_suffix)
	{
		nb_word = count_words(cmd_suffix);
		exec_cmd_suffix(cmd_suffix, &redirect_list, av + nb_word);
	}
	exec_dup(redirect_list);
	
	if ((fct_body = get_function(singleton_env(), av[0]))) // si cmd name est le nom d une fct -> exec func
		return (exec_function(fct_body, av));

	if (get_exec_builtin(av[0]))
		return (exec_builtin(singleton_env(), (const char **)av));
	exec_bin(singleton_env(), (const char **)av);
	close_dup(redirect_list);
	return (EXIT_SUCCESS);
}
