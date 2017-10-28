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
		printf("no process ready to report\n");
		/* No processes ready to report.  */
		return -1;
	}
	else {
		/* Other weird errors.  */
		perror ("waitpid");
		return -1;
	}
}

/* Check for processes that have status information available,
**    without blocking.  */

void	update_status(t_job_control *jc)
{
	int status;
	pid_t pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED|WNOHANG);
	while (!mark_process_status(jc, pid, status))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED|WNOHANG);
}

/* Check for processes that have status information available,
**    blocking until all processes in the given t_t_job have reported.  */

void	wait_for_job(t_job_control *jc, t_job *j)
{
	int status;
	pid_t pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	while (!mark_process_status(jc, pid, status)
			&& !job_is_stopped(j)
			&& !job_is_completed(j))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
}

/* Format information about t_job status for the user to look at.  */

void	format_job_info(t_job *j, const char *status)
{
	fprintf(stderr, "%ld (%s): %s\n", (long)j->pgid, status, j->command);
}

/* Notify the user about stopped or terminated jobs.
**    Delete terminated jobs from the active t_job list.  */

void	do_job_notification(t_job_control *jc)
{
	t_job		*j;
	t_job		*jlast;
	t_job		*jnext;

	/* Update status information for child processes.  */
	update_status (jc);
	jlast = NULL;
	j = jc->first_job;
	while (j)
	{
		jnext = j->next;

		/* If all processes have completed, tell the user the t_job has
		**          completed and delete it from the list of active jobs.  */
		if (job_is_completed (j)) {
			format_job_info (j, "completed");
			if (jlast)
				jlast->next = jnext;
			else
				jc->first_job = jnext;
			//free_job (j);
		}

		/* Notify the user about stopped jobs,
		**          marking them so that we won’t do this more than once.  */
		else if (job_is_stopped (j) && !j->notified) {
			format_job_info (j, "stopped");
			j->notified = 1;
			jlast = j;
		}

		/* Don’t say anything about jobs that are still running.  */
		else
			jlast = j;
	}
	j = jnext;
}
