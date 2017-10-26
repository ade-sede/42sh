/*
**	while_clause     : While compound_list do_group
*/

int exec_while_clause(t_ast *ast)
{
	while (exec(ast->child[1]) == EXIT_SUCCESS)
		exec(ast->child[2]);
	return (EXIT_SUCCESS);
}
