
/* Keep track of attributes of the shell.  */

#include "job_control.h"
#include "line_editing.h"


/* Make sure the shell is running interactively as the foreground job
   before proceeding. */

void	init_job_control(t_job_control *jc)
{

	/* See if we are running interactively.  */
	jc->shell_terminal = STDIN_FILENO;
	jc->shell_is_interactive = isatty(jc->shell_terminal);

	if (jc->shell_is_interactive)
	{
		printf("shell is interactive\n");
		/* Loop until we are in the foreground.  */
		while (tcgetpgrp(jc->shell_terminal) != (jc->shell_pgid = getpgrp()))
		{
			printf("kill ourself\n");
			kill(-jc->shell_pgid, SIGTTIN);
		}
		/* Ignore interactive and job-control signals.  */
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
//		signal(SIGCHLD, SIG_IGN);

		/* Put ourselves in our own process group.  */
//		dprintf(2, "\nprocess group: %d, process id: %d\n", getpgrp(), getpid());
		jc->shell_pgid = getpid();
		if (setpgid(jc->shell_pgid, jc->shell_pgid) < 0)
		{
			perror ("Couldn't put the shell in its own process group");
			exit(1);
		}

		/* Grab control of the terminal.  */
		tcsetpgrp(jc->shell_terminal, jc->shell_pgid);
	}
}
