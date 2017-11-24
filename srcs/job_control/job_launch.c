#include "job_control.h"
#include "exec.h"

void	quit_job(int signum)
{
	(void)signum;
	kill(-getpgrp(), SIGQUIT); 
}

void	launch_process(t_job_control *jc, t_process *p, pid_t pgid,
		int infile, int outfile, int errfile,
		int foreground,
		int in_a_fork)
{
	pid_t	pid;

	(void)foreground;
	if (jc->shell_is_interactive)
	{
		pid = getpid();
		if (pgid == 0)
			pgid = pid;
		setpgid(pid, pgid);
		if (!in_a_fork && foreground && !jc->background)
		{
		//	fprintf(stderr, "put controling terminal");
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
			signal(SIGTTOU, SIG_DFL); //attention
		}
		signal(SIGCHLD, SIG_DFL);
	}
	if (infile != STDIN_FILENO)
	{
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	if (outfile != STDOUT_FILENO)
	{
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
	if (errfile != STDERR_FILENO)
	{
		dup2(errfile, STDERR_FILENO);
		close(errfile);
	}
	exit(exec(p->command));
	//exit(singleton_env()->previous_exit);
}

int		launch_job(t_job_control *jc, t_job *j, int foreground)
{
	t_process	*p;
	pid_t	pid;
	int		mypipe[2];
	int		infile;
	int		outfile;
	pid_t	parent_process_group_id;
	int		in_a_fork = 0;

	if (!j->pgid)
	{
		if ((parent_process_group_id = getpgid(0)) != jc->shell_pgid)
		{
			j->pgid = parent_process_group_id;
			in_a_fork = 1;
		}
//		else if (foreground)
//			fprintf(stderr, "put controling terminal");
	}
	infile = j->stdin;
	p = j->first_process;
	while (p)
	{
		if (p->next)
		{
			p_pipe(mypipe);
			outfile = mypipe[1];
		}
		else
			outfile = j->stdout;
		pid = p_fork();
		if (pid == 0)
			launch_process(jc, p, j->pgid, infile,
					outfile, j->stderr, foreground, in_a_fork);
		else
		{
			p->pid = pid;
			if (jc->shell_is_interactive)
			{
				if (!j->pgid)
					j->pgid = pid;
				setpgid(pid, j->pgid);
			}
		}
		if (infile != j->stdin)
			close(infile);
		if (outfile != j->stdout)
			close(outfile);
		infile = mypipe[0];
		p = p->next;
	}
	if (!jc->shell_is_interactive || jc->background)
	{
//		fprintf(stderr, "shell not interactiv || background\n");
		return (wait_for_job(jc, j));
	}
	else if (foreground)
	{
//		fprintf(stderr, "foreground\n");
		return (put_job_in_foreground(jc, j, 0, in_a_fork));
	}
	else
	{
//		fprintf(stderr, "ackground\n");
		return (put_job_in_background(j, 0));
	}
}
