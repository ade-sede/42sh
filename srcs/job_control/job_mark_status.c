#include "job_control.h"

int		mark_process_status(t_job_control *jc, pid_t pid, int status)
{
	t_job *j;
	t_process *p;

	if (pid == 0 || errno == ECHILD)
		return -1;
	j = jc->first_job;
	while (j)
	{
		p = j->first_process;
		while (p)
		{
			if (p->pid == pid)
			{
//				dprintf(2, "mark process_status pid found\n");
				p->status = status;
				if (WIFSTOPPED(status))
					p->stopped = 1;
				else
				{
					p->completed = 1;
					if (WIFSIGNALED(status))
						p->signaled = 1;
				}
				return (0);
			}
			p = p->next;
		}
		j = j->next;
	}
	fprintf (stderr, "No child process %d.\n", pid);
	return (-1);
}
