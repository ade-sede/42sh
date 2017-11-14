void	read_heredoc()
{
	ast->heredoc = get_input();
}
void	parse_heredoc(t_ast *ast)
{
	int		i = 0;

	if (!ast)
		return ;
	while (ast->child[i] && i < 7)
	{

		parse_heredoc(ast->child[i]);
		if (is_symb(ast, IO_HERE))
			read_heredoc(ast);
		i++;
	}
	free(ast);
}

