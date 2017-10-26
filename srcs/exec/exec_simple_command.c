/*
**	simple_command   : cmd_prefix cmd_word cmd_suffix
**	                 | cmd_prefix cmd_word
**	                 | cmd_prefix
**	                 | cmd_name cmd_suffix
**	                 | cmd_name
*/

int		exec_simple_command(t_ast *ast)
{
	char	*av[4096];
	t_list	*redirect_list;
	t_ast	*cmd_suffix;

	exec_cmd_prefix(ast, av);
	if (is_symb(ast->child[0], CMD_PREFIX))
		exec_cmd_prefix(ast->child[0], &redirect_list);

	if (is_symb(ast->child[1], CMD_WORD))
		av[0] = extract_word(ast->child[1]->child[0]);
	else if (is_symb(ast->child[0], CMD_NAME))
		av[0] = extract_word(ast->child[0]->child[0]);

	if (is_sym(ast->child[1], CMD_SUFFIX))
		cmd_suffix = ast->child[1];
	if (is_sym(ast->child[2], CMD_SUFFIX))
		cmd_suffix = ast->child[2];
	if (cmd_suffix)
		exec_cmd_suffix(cmd_suffix, &redirect_list, av[0] ? av + 1 : av);

	exec_dup(redir_stack);
	exec(singleton_env(), av, redir_list);
	inverse_list(redir_list);
	close_dup(redir_list);
}

/*
**	cmd_suffix       :            io_redirect
**	                 | cmd_suffix io_redirect
**	                 |            WORD
**	                 | cmd_suffix WORD
*/

void	exec_cmd_suffix(t_ast	*ast, t_list *redirect_list char **av)
{
	t_ast	*io_redirect = NULL;

	if (ast->child[0]->symbol == io_redirect)
		io_redirect = ast->child[0];
	else if (ast->child[1] && ast->child[1]->symbol == io_redirect)
		io_redirect = ast->child[1];
	if (is_token(ast->child[0], TK_WORD))
		assignement_word = ast->child[0];
	else if (is_token(ast->child[1], TK_WORD))
	{
		*av = ft_strdup(ast->child[1]->token->value);
		av++;
	}
	if (io_redirect)
		exec_io_redirect(io_redirect, redirect_list);
	if (ast->child[0]->symbol == CMD_SUFFIX)
		exec_cmd_suffix(ast->child[0], redirect_list, av);
}

/*
**	cmd_prefix       :            io_redirect
**	                 | cmd_prefix io_redirect
**	                 |            ASSIGNMENT_WORD
**	                 | cmd_prefix ASSIGNMENT_WORD
**	                 ;
*/

void	exec_cmd_prefix(t_ast	*ast, t_list **redirect_list)
{
	t_ast	*assignement_word = NULL;
	t_ast	*io_redirect = NULL;

	if (ast->child[0]->symbol == io_redirect)
		io_redirect = ast->child[0];
	else if (ast->child[1] && ast->child[1]->symbol == io_redirect)
		io_redirect = ast->child[1];
	if (is_token(ast->child[0], TK_ASSIGNMENT_WORD))
		assignement_word = ast->child[0];
	else if (is_token(ast->child[1], TK_ASSIGNEMENT_WORD))
		assignement_word = ast->child[1];
	if (assignement_word)
		exec_assignement_word(assignement_word);
	if (io_redirect)
		exec_io_redirect(io_redirect, redirect_list);
	if (ast->child[0]->symbol == CMD_PREFIX)
		exec_cmd_prefix(ast->child[0]);
}

void	exec_assignement_word(t_ast *ast)
{
	add_to_local(&singleton_env()->local, ft_strdup(ast->token->value));
}

char	*extract_word(t_ast *ast)
{
	return (ft_strdup(ast->token->value));
}
