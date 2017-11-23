#include "job_control.h"
#include "line_editing.h"

int		put_job_in_foreground(t_job_control *jc, t_job *j, int cont, \
		int in_a_fork)
{
	int		exit_status;

	j->foreground = 1;
	if (!in_a_fork)
		tcsetpgrp(jc->shell_terminal, j->pgid);
	if (cont)
	{
		conf_term_canonical();
		if (kill(-j->pgid, SIGCONT) < 0)
			perror("kill (SIGCONT)");
	}
	exit_status = wait_for_job(jc, j);
	if (!in_a_fork)
	{
		tcsetpgrp(jc->shell_terminal, jc->shell_pgid);
		do_job_notification(singleton_jc());
	}
	return (exit_status);
}
