#include "job_control.h"
#include <stdlib.h>

t_job		*find_job(t_job_control *jc, pid_t pgid)
{
	t_job *j;

	j = jc->first_job;
	while (j)
	{
		if (j->pgid == pgid)
			return (j);
		j = j->next;
	}
	return (NULL);
}

t_job		*job_new(void)
{
	t_job	*new;

	new = ft_memalloc(sizeof(t_job));
	new->stdin = STDIN_FILENO;
	new->stdout = STDOUT_FILENO;
	new->stderr = STDERR_FILENO;
	return (new);
}

t_process	*process_new(t_ast *command)
{
	t_process	*new;

	new = ft_memalloc(sizeof(t_process));
	new->command = command;
	new->av = ft_strnew(1);
	return (new);
}

void		job_free(t_job *job)
{
	t_process	*process;
	t_process	*process_next;

	process = job->first_process;
	while (process)
	{
		process_next = process->next;
		free(process->av);
		free(process);
		process = process_next;
	}
	free(job);
}
