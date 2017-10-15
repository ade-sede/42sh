#include "job_control.h"
#include "line_editing.h"

/* Put job j in the foreground.  If cont is nonzero,
**    restore the saved terminal modes and send the process group a
**       SIGCONT signal to wake it up before we block.  */

void	put_job_in_foreground(t_job_control *jc, t_job *j, int cont)
{
	/* Put the job into the foreground.  */
	tcsetpgrp(jc->shell_terminal, j->pgid);

	/* Send the job a continue signal, if necessary.  */
	if (cont)
	{
		conf_term_normal();
		if (kill(-j->pgid, SIGCONT) < 0)
			perror ("kill (SIGCONT)");
	}

	/* Wait for it to report.  */
	wait_for_job(j);

	/* Put the shell back in the foreground.  */
	tcsetpgrp(jc->shell_terminal, jc->shell_pgid);

	/* Restore the shell’s terminal modes.  */
	conf_term_canonical();
}
