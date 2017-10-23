#include "job_control.h"

void	launch_process(t_job_control *jc, t_process *p, pid_t pgid,
		int infile, int outfile, int errfile,
		int foreground)
{
	pid_t	pid;

	if (jc->shell_is_interactive)
	{
		/* Put the process into the process group and give the process group
		**          the terminal, if appropriate.
		**                   This has to be done both by the shell and in the individual
		**                            child processes because of potential race conditions.  */
		pid = getpid();
		if (pgid == 0)
			pgid = pid;
		setpgid(pid, pgid);
		if (foreground)
			tcsetpgrp(jc->shell_terminal, pgid);

		/* Set the handling for job control signals back to the default.  */
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		signal(SIGTTIN, SIG_DFL);
		signal(SIGTTOU, SIG_DFL);
		signal(SIGCHLD, SIG_DFL);
	}
	/* Set the standard input/output channels of the new process.  */
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
	/* Exec the new process.  Make sure we exit.  */
	exec_bin(singleton_env(), p->argv);
	exit(1);
}

void	launch_job(t_job_control *jc, t_job *j, int foreground)
{
	t_process	*p;
	pid_t	pid;
	int		mypipe[2];
	int		infile;
	int		outfile;

	infile = j->stdin;
	p = j->first_process;
	while (p)
	{
		if (p->next)
		{
			if (pipe (mypipe) < 0)
			{
				perror ("pipe");
				exit (1);
			}
			outfile = mypipe[1];
		}
		else
			outfile = j->stdout;
		pid = fork ();
		if (pid == 0)
			launch_process(jc, p, j->pgid, infile,
					outfile, j->stderr, foreground);
		else if (pid < 0)
		{
			perror ("fork");
			exit (1);
		}
		else
		{
			p->pid = pid;
			if (jc->shell_is_interactive)
			{
				if (!j->pgid)
					j->pgid = pid;
				setpgid (pid, j->pgid);
			}
		}
		if (infile != j->stdin)
			close(infile);
		if (outfile != j->stdout)
			close(outfile);
		infile = mypipe[0];
		p = p->next;
	}
	format_job_info (j, "launched");
	if (!jc->shell_is_interactive)
		wait_for_job(jc, j);
	else if (foreground)
		put_job_in_foreground(jc, j, 0);
	else
		put_job_in_background(j, 0);
}