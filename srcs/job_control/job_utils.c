#include "job_control.h"
#include <stdlib.h>

t_job	*find_job(t_job_control *jc, pid_t pgid)
{
	t_job *j;

	j = jc->first_job;
	while (j)
	{
		if (j->pgid == pgid)
			return j;
		j = j->next;
	}
	return (NULL);
}

int	job_is_stopped(t_job *j)
{
	t_process *p;

	for (p = j->first_process; p; p = p->next)
		if (!p->completed && !p->stopped)
			return (0);
	return (1);
}


int	job_is_completed(t_job *j)
{
	t_process *p;

	for (p = j->first_process; p; p = p->next)
		if (!p->completed)
			return (0);
	return (1);
}

t_job	*job_new()
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

void	job_add(t_job *new, t_job **first_job)
{
	new->next = *first_job;
	*first_job = new;
}

t_job	*get_last_job(t_job *j)
{
	while (j && j->next)
		j = j->next;
	return (j);
}

void	job_pushback(t_job *new, t_job **first_job)
{
	t_job	*j;

	if (!*first_job)
		return (job_add(new, first_job));
	j = *first_job;
	while (j && j->next)
		j = j->next;
	j->next = new;
}
void	process_add(t_process *new, t_process **first_process)
{
	new->next = *first_process;
	*first_process = new;
}

void	job_free(t_job *job)
{
	t_process	*process;
	t_process	*process_next;

	process = job->first_process;
	while (process)
	{
		process_next = process->next;
		free_ast(process->command);
		free(process->av);
		free(process);
		process = process_next;
	}
}
