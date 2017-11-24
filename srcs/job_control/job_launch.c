#include "job_control.h"
#include "exec.h"

void	quit_job(int signum)
{
	(void)signum;
	kill(-getpgrp(), SIGQUIT);
}

static void		close_std(int *stdfile, t_job *j, int state)
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

static void		launch_process(t_job_control *jc, pid_t pgid, int foreground,
		int in_a_fork)
{
	pid_t	pid;

	if (jc->shell_is_interactive)
	{
		pid = getpid();
		pgid = (pgid == 0) ? pid : 0;
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

static int		ret_job(t_job_control *jc, t_job *j, int foreground,
		int in_a_fork)
{
	if (!jc->shell_is_interactive || jc->background)
		return (wait_for_job(jc, j));
	else if (foreground)
		return (put_job_in_foreground(jc, j, 0, in_a_fork));
	return (put_job_in_background(j, 0));
}

static void		cut1(t_job_control *jc, t_job *j, t_process *process, pid_t pid)
{
	process->pid = pid;
	if (jc->shell_is_interactive)
	{
		if (!j->pgid)
			j->pgid = pid;
		setpgid(pid, j->pgid);
	}
}

static int		init_launch(t_job_control *jc, t_job *j, int *stdfile)
{
	int			in_a_fork;
	pid_t		parent_process_group_id;

	in_a_fork = 0;
	stdfile[0] = j->stdin;
	stdfile[1] = j->stdout;
	stdfile[2] = j->stderr;
	if (!j->pgid)
	{
		if ((parent_process_group_id = getpgid(0)) != jc->shell_pgid)
		{
			j->pgid = parent_process_group_id;
			in_a_fork = 1;
		}
	}
	return (in_a_fork);
}

static int		cut_pipe(int *mypipe)
{
	p_pipe(mypipe);
	return (mypipe[1]);
}

int				launch_job(t_job_control *jc, t_job *j, int foreground)
{
	t_process	*process;
	pid_t		pid;
	int			mypipe[2];
	int			stdfile[3];
	int			in_a_fork;

	in_a_fork = init_launch(jc, j, stdfile);
	process = j->first_process;
	while (process)
	{
		stdfile[1] = j->stdout;
		if (process->next)
			stdfile[1] = cut_pipe(mypipe);
		if ((pid = p_fork()) == 0)
		{
			launch_process(jc, j->pgid, foreground, in_a_fork);
			close_std(stdfile, j, 0);
			exit(exec(process->command));
		}
		else
			cut1(jc, j, process, pid);
		close_std(stdfile, j, mypipe[0]);
		process = process->next;
	}
	return (ret_job(jc, j, foreground, in_a_fork));
}
