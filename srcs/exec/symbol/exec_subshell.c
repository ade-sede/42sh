#include "exec.h"

/*
**	subshell         : '(' compound_list ')'
*/

int exec_subshell(t_ast *ast) 
{
	t_job	*new_job;
	t_process	*first_process;

	new_job = job_new();
	first_process = process_new(ast->child[1]);
	new_job->first_process = first_process;
	ft_genlst_pushback(&singleton_jc()->first_job, new_job);
	launch_job(singleton_jc(), new_job, 1);
	return (new_job->exit_status);
}
