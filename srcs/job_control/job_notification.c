#include "job_control.h"

void	do_job_notification(t_job_control *jc)
{
	t_job		*j;
	t_job		*jlast;
	t_job		*jnext;

	update_status(jc);
	jlast = NULL;
	j = jc->first_job;
	while (j)
	{
		jnext = j->next;
		if (job_is_completed(j))
		{
			if (!j->foreground && jc->shell_is_interactive)
				format_job_info_process(j, "done");
			if (jlast)
				jlast->next = jnext;
			else
				jc->first_job = jnext;
			job_free(j);
		}
		else if (job_is_stopped(j) && !j->notified)
		{
			format_job_info_process(j, "stopped");
			j->notified = 1;
			jlast = j;
		}
		else
			jlast = j;
		j = jnext;
	}
}
