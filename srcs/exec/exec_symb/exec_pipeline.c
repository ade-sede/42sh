#include "exec.h"
#include "builtin.h"
#include "job_control.h"
#include "hash_table.h"
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
	t_ast	*simple_command;

	if (pipe_sequence->child[3] != NULL)
		return (1);
	simple_command = pipe_sequence->child[0]->child[0];
	if (is_symb(simple_command, SIMPLE_COMMAND) && !get_exec_builtin(get_cmd_name(simple_command)))
		return (1);
	return (0);
}

t_process	*fill_process(t_ast *ast, t_process *process)
{
	int	i;
	t_ast	*child;

	i = 0;
	while (ast && ast->child[i])
	{
		child = ast->child[i];
		if (child && child->token)
			process->av = ft_strjoin3_free(process->av, " ", child->token->value, 4);
		else
			fill_process(child, process);
		i++;
	}
	return (process);
}

void	fill_job(t_ast *pipe_sequence, t_process **first_process)
{
	if (pipe_sequence->child[0] && !pipe_sequence->child[3])
		return (ft_genlst_add(first_process, fill_process(pipe_sequence->child[0], process_new(pipe_sequence->child[0]))));
	if (pipe_sequence->child[0] && pipe_sequence->child[3])
	{
		ft_genlst_add(first_process, fill_process(pipe_sequence->child[3], process_new(pipe_sequence->child[3])));
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
//		debug_process(first_process);
		new_job->first_process = first_process;
		ft_genlst_pushback(&singleton_jc()->first_job, new_job);
		launch_job(singleton_jc(), new_job, 1);
		exit_status = new_job->exit_status;
	}
	else
		exit_status = exec(pipe_sequence);
	if (is_token(ast->child[0], TK_BANG))
		return (exit_status > 0 ? EXIT_SUCCESS : EXIT_FAILURE);
	return (exit_status);
}
