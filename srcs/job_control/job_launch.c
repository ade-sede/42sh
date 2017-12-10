/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_launch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:36 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:23 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
	mypipe[0] = j->stdin;
	while (process)
	{
		stdfile[1] = j->stdout;
		if (process->next)
			stdfile[1] = cut_pipe(mypipe);
		if ((pid = p_fork()) == 0)
		{
			launch_process(jc, j->pgid, foreground, in_a_fork);
			close_std(stdfile, j, 0);
			if (mypipe[0])
				close(mypipe[0]);
			exit(exec(process->command));
		}
		else
			cut1(jc, j, process, pid);

		close_std(stdfile, j, mypipe[0]);
		process = process->next;
	}
	return (ret_job(jc, j, foreground, in_a_fork));
}
