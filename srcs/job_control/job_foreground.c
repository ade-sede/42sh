/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_foreground.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:36 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:22 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "failure.h"
#include "line_editing.h"

int		put_job_in_foreground(t_job_control *jc, t_job *j, int cont, \
		int in_a_fork)
{
	int		exit_status;

	j->foreground = 1;
	if (!in_a_fork)
		tcsetpgrp(jc->shell_terminal, j->pgid);
	if (cont)
	{
		conf_term_canonical();
		if (kill(-j->pgid, SIGCONT) < 0)
			investigate_error(1, "kill (SIGCONT)", NULL, 0);
	}
	exit_status = wait_for_job(jc, j);
	if (!in_a_fork)
	{
		tcsetpgrp(jc->shell_terminal, jc->shell_pgid);
		do_job_notification(singleton_jc());
	}
	return (exit_status);
}
