#include "job_control.h"

/* Store the status of the process pid that was returned by waitpid.
**    Return 0 if all went well, nonzero otherwise.  */

int		mark_process_status(t_job_control *jc, pid_t pid, int status)
{
	t_job *j;
	t_process *p;

	if (pid > 0)
	{
		/* Update the record for the process.  */
		j = jc->first_job;
		while (j)
		{
			p = j->first_process;
			while (p)
			{
				if (p->pid == pid)
				{
					p->status = status;
					if (WIFSTOPPED(status))
						p->stopped = 1;
					else
					{
						p->completed = 1;
						if (WIFSIGNALED(status))
							fprintf (stderr, "%d: Terminated by signal %d.\n",
									(int) pid, WTERMSIG (p->status));
					}
					return 0;
				}
				p = p->next;
			}
			j = j->next;
		}
		fprintf (stderr, "No child process %d.\n", pid);
		return -1;
	}
	else if (pid == 0 || errno == ECHILD)
	{
		perror("no process ready to report");
		/* No processes ready to report.  */
		return -1;
	}
	else {
		/* Other weird errors.  */
		perror ("waitpid");
		return -1;
	}
}

void	update_status(t_job_control *jc)
{
	int status;
	pid_t pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED|WNOHANG);
	while (!mark_process_status(jc, pid, status))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED|WNOHANG);
}

void	get_exit_status(t_job *j)
{
	t_process	*p;

	p = j->first_process;
	while (p && p->next)
		p = p->next;
	if (WIFEXITED(p->status))
		j->exit_status = WEXITSTATUS(p->status);
	else if (p->stopped)
		j->exit_status = EXIT_FAILURE;
	else if (WIFSIGNALED(p->status))
		j->exit_status = EXIT_FAILURE;
}

void	wait_for_job(t_job_control *jc, t_job *j)
{
	int status;
	pid_t pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	while (!mark_process_status(jc, pid, status)
			&& !job_is_stopped(j)
			&& !job_is_completed(j))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	get_exit_status(j);
}

/* Format information about t_job status for the user to look at.  */

void	format_job_info(t_job *j, const char *status)
{
	fprintf(stderr, "%ld (%s): %s\n", (long)j->pgid, status, j->command);
}

int		job_number(t_job *j)
{
	t_job	*first_job;
	int		i;

	i = 1;
	first_job = singleton_jc()->first_job;
	while (first_job && first_job != j)
	{
		i++;
		first_job = first_job->next;
	}
	return (i);
}

void	format_job_info_process(t_job *j, const char *status)
{
	t_process	*p;
	char		*job_no;
	size_t		job_no_length;

	job_no = ft_itoa(job_number(j));
	job_no_length = ft_strlen(job_no);
	fprintf(stderr, "[%d]", job_number(j));
	p = j->first_process;
	fprintf(stderr, " %ld %s: %s%s\n ", (long)p->pid, status, p->av, p->next ? " |" : "");
	p = p->next;
	while (p)
	{
		ft_putnstr("                ", job_no_length + 2);
		fprintf(stderr, "%ld %s: %s%s\n ", (long)p->pid, status, p->av, p->next ? " |" : "");
		p = p->next;
	}
}

void	do_job_notification(t_job_control *jc)
{
	t_job		*j;
	t_job		*jlast;
	t_job		*jnext;

	update_status (jc);
	jlast = NULL;
	j = jc->first_job;
	while (j)
	{
		jnext = j->next;
		if (job_is_completed (j)) {
			format_job_info_process (j, "completed");
			if (jlast)
				jlast->next = jnext;
			else
				jc->first_job = jnext;
		//	free_job (j);
		}
		else if (job_is_stopped (j) && !j->notified) {
			format_job_info_process (j, "stopped");
			j->notified = 1;
			jlast = j;
		}
		else
			jlast = j;
		j = jnext;
	}
}
