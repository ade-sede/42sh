#include "job_control.h"
#include "line_editing.h"

void	put_job_in_foreground(t_job_control *jc, t_job *j, int cont, int in_a_fork)
{
	(void)in_a_fork;
	
//	fprintf(stderr, "in a fork %d", in_a_fork);
	if (!in_a_fork)
		tcsetpgrp(jc->shell_terminal, j->pgid);
	if (cont)
	{
		conf_term_normal();
		if (kill(-j->pgid, SIGCONT) < 0)
			perror ("kill (SIGCONT)");
	}
	wait_for_job(jc, j);
	if (!in_a_fork)
		tcsetpgrp(jc->shell_terminal, jc->shell_pgid);
}
