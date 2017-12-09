/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_wait.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:36 by ade-sede          #+#    #+#             */
/*   Updated: 2017/12/09 17:25:05 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include <errno.h>
#include "job_control.h"
#include "color.h"
#include "failure.h"
#ifdef __linux__
# include <sys/wait.h>
#endif

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
	int		sig;

	p = j->first_process;
	while (p && p->next)
		p = p->next;
	if (WIFEXITED(p->status))
		return (WEXITSTATUS(p->status));
	else if (p->stopped)
		return (EXIT_FAILURE);
	else if (WIFSIGNALED(p->status))
	{
		sig = 128 + WTERMSIG(p->status);
		//if (sig != 130)
		//	ft_putstr_fd(MAG"42sh: "RESET, 2);
		ft_putstr_fd(get_errsig(sig), 2);
		return (sig);
	}
	return (EXIT_SUCCESS);
}

int		wait_for_job(t_job_control *jc, t_job *j)
{
	int		status;
	pid_t	pid;

	errno = 0;
	while ((pid = waitpid(WAIT_ANY, &status, WUNTRACED)) > -1)
	{
		//pid = waitpid(WAIT_ANY, &status, WUNTRACED);
		if (!(!mark_process_status(jc, pid, status)
					&& !job_is_stopped(j)
					&& !job_is_completed(j)))
			break ;
		errno = 0;
	}
	return (get_job_exit_status(j));
}
