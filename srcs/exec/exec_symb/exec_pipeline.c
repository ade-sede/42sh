/*
**	pipeline         :      pipe_sequence
**	                 | Bang pipe_sequence
*/

int exec_pipeline(t_ast *ast)
{
	int		exit_status;
	t_process	*first_process;
	t_job	*new_job;

	/*
**		if (ast->child[0]->symbol == Bang)
**		{
**			exit_status = exec(ast->child[1]);
**			return (exit_status > 0 ? 0 : exit_status);
**		}
**		return (exec(ast->child[0]));
*/
	new_job = job_new();
	fill_job(pipe_sequence, &first_process);
	new_job->first_process = first_process;
	lauch_job(singleton_jc(), new_job, 1);
}

/*
**	pipe_sequence    :                             command
**	                 | pipe_sequence '|' linebreak command
*/

void	fill_job(t_ast *pipe_sequence, t_process **process)
{
	if (ast->child[0] && !ast->child[2])
		return (process_add(process_new(pipe_sequence->child[0])));
	if (ast->child[0] && ast->child[2])
	{
		process_add(process_new(pipe_sequence->child[2]), process);
		fill_job(pipe_sequence->child[0], process);
	}
}
