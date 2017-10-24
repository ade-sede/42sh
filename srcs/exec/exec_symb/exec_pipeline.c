/*
**	pipeline         :      pipe_sequence
**	                 | Bang pipe_sequence
*/

int exec_pipeline(t_ast *ast)
{
	int		exit_status;

	if (ast->child[0]->symbol == Bang)
	{
		exit_status = exec(ast->child[1]);
		return (exit_status > 0 ? 0 : exit_status);
	}
	return (exec(ast->child[0]));
}
