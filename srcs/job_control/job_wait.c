/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_wait.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:36 by ade-sede          #+#    #+#             */
/*   Updated: 2017/12/09 12:37:02 by seddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include <errno.h>
#include "job_control.h"
#include "color.h"
#include "failure.h"
#include "line_editing.h"

void	update_status(t_job_control *jc)
{
	int		status;
	pid_t	pid;

	while (42)
	{
		errno = 0;
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
		if (!(!mark_process_status(jc, pid, status)))
			break ;
	}
}

int		get_job_exit_status(t_job *j)
{
	t_process	*p;
	int		signum;

	p = j->first_process;
	while (p && p->next)
		p = p->next;
	if (WIFEXITED(p->status))
		return (WEXITSTATUS(p->status));
	else if (p->stopped)
		return (128 + WEXITSTATUS(p->status));
	else if (WIFSIGNALED(p->status))
	{
		signum = 128 + WTERMSIG(p->status);
		if (signum != 130 && signum != 131)
			ft_putstr_fd(RED"42sh: "RESET, 2);
		ft_putstr_fd(get_errsig(signum), 2);
		return (signum);
	}
	return (EXIT_SUCCESS);
}

int		wait_for_job(t_job_control *jc, t_job *j)
{
	int		status;
	pid_t	pid;

	errno = 0;
	while (42)
	{
		errno = 0;
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
		if (!(!mark_process_status(jc, pid, status)
					&& !job_is_stopped(j)
					&& !job_is_completed(j)))
			break ;
	}
	return (get_job_exit_status(j));
}
