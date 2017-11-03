#include "job_control.h"
#include "line_editing.h"


void	init_job_control(t_job_control *jc)
{

	jc->shell_terminal = STDIN_FILENO;
	jc->shell_is_interactive = isatty(jc->shell_terminal);

	if (jc->shell_is_interactive)
	{
		printf("shell is interactive\n");
		while (tcgetpgrp(jc->shell_terminal) != (jc->shell_pgid = getpgrp()))
		{
			printf("kill ourself\n");
			kill(-jc->shell_pgid, SIGTTIN);
		}
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
//		signal(SIGCHLD, SIG_IGN);

		jc->shell_pgid = getpid();
		if (setpgid(jc->shell_pgid, jc->shell_pgid) < 0)
		{
			perror ("Couldn't put the shell in its own process group");
			exit(1);
		}

		tcsetpgrp(jc->shell_terminal, jc->shell_pgid);
	}
}
