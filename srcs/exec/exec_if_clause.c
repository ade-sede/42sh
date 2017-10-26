/*
**					  0       1         2        3            4     5
** if_clause        : If compound_list Then compound_list else_part Fi
**					| If compound_list Then compound_list           Fi
*/

int exec_if_clause(t_ast *ast)
{


	if (exec(ast->child[1]) == EXIT_SUCCESS)
		return (exec(ast->child[3]));
	else if (ast->child[5])
		return (exec(ast->child[4]))
	return (exit_status);
}
