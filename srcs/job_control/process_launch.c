#include "job_control.h"
#include "exec.h"

void	quit_job(int signum)
{
	(void)signum;
	kill(-getpgrp(), SIGQUIT);
}

void	close_std(int *stdfile, t_job *j, int state)
{
	if (!state)
	{
		if (stdfile[0] != STDIN_FILENO)
		{
			dup2(stdfile[0], STDIN_FILENO);
			close(stdfile[0]);
		}
		if (stdfile[1] != STDOUT_FILENO)
		{
			dup2(stdfile[1], STDOUT_FILENO);
			close(stdfile[1]);
		}
		if (stdfile[2] != STDERR_FILENO)
		{
			dup2(stdfile[2], STDERR_FILENO);
			close(stdfile[2]);
		}
		return ;
	}
	if (stdfile[0] != j->stdin)
		close(stdfile[0]);
	if (stdfile[1] != j->stdout)
		close(stdfile[1]);
	stdfile[0] = state;
}

void	launch_process(t_job_control *jc, pid_t pgid, int foreground,
		int in_a_fork)
{
	pid_t	pid;

	if (jc->shell_is_interactive)
	{
		pid = getpid();
		pgid = (pgid == 0) ? pid : pgid;
		setpgid(pid, pgid);
		if (!in_a_fork && foreground && !jc->background)
		{
			if (tcsetpgrp(jc->shell_terminal, pgid) == -1)
				perror("tcsetpgrp:");
			if (foreground)
				signal(SIGINT, quit_job);
		}
		if (!foreground)
			jc->background = 1;
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		if (!foreground)
		{
			signal(SIGTTIN, SIG_DFL);
			signal(SIGTTOU, SIG_DFL);
		}
		signal(SIGCHLD, SIG_DFL);
	}
}
