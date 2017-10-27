#include "exec.h"
#include "job_control.h"
/*
**	pipeline         :      pipe_sequence
**	                 | Bang pipe_sequence
*/


/*
**	pipe_sequence    :                             command
**	                 | pipe_sequence '|' linebreak command
*/

int		pipe_sequence_has_to_fork(t_ast	*pipe_sequence)
{
//	t_ast	*simple_command;

	if (pipe_sequence->child[3] != NULL)
		return (1);
//	simple_command = pipe_sequence->child[0]->child[0];
//	if (is_symb(simple_command, SIMPLE_COMMAND) && !is_builtin(simple_command))
		return (1);
	return (0);
}

void	fill_job(t_ast *pipe_sequence, t_process **first_process)
{
	if (pipe_sequence->child[0] && !pipe_sequence->child[3])
		return (process_add(process_new(pipe_sequence->child[0]), first_process));
	if (pipe_sequence->child[0] && pipe_sequence->child[3])
	{
		process_add(process_new(pipe_sequence->child[3]), first_process);
		fill_job(pipe_sequence->child[0], first_process);
	}
}


void	debug_process(t_process *first_process)
{
		printf("----\n");
	while (first_process)
	{
		debug_symbol(first_process->command);
		first_process = first_process->next;
	}
		printf("----\n");
}

int exec_pipeline(t_ast *ast)
{
	int		exit_status;
	t_process	*first_process = NULL;
	t_job	*new_job;
	t_ast	*pipe_sequence;

	
	if (is_token(ast->child[0], TK_BANG))
		pipe_sequence = ast->child[1];
	else
		pipe_sequence = ast->child[0];
	if (pipe_sequence_has_to_fork(pipe_sequence))
	{
		new_job = job_new();
		fill_job(pipe_sequence, &first_process);
		new_job->first_process = first_process;
		debug_process(new_job->first_process);
		launch_job(singleton_jc(), new_job, 1);
		return (42);
	}
	if (is_token(ast->child[0], TK_BANG))
	{
		exit_status = exec(ast->child[1]);
		return (exit_status > 0 ? 0 : exit_status);
	}
	return (exec(ast->child[0]));
}
