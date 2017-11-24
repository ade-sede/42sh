/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:36 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:23 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "failure.h"
#include "line_editing.h"
#include "printf.h"

void	init_job_control(t_job_control *jc)
{
	jc->shell_terminal = STDIN_FILENO;
	jc->shell_is_interactive = isatty(jc->shell_terminal);
	if (jc->shell_is_interactive)
	{
		while (tcgetpgrp(jc->shell_terminal) != (jc->shell_pgid = getpgrp()))
		{
			ft_dprintf(2, "kill ourself\n");
			kill(-jc->shell_pgid, SIGTTIN);
		}
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
		jc->shell_pgid = getpid();
		if (setpgid(jc->shell_pgid, jc->shell_pgid) < 0)
		{
			investigate_error(1, "setpgid", \
				"Couldn't put the shell in its own process group", 0);
			exit(1);
		}
		tcsetpgrp(jc->shell_terminal, jc->shell_pgid);
	}
}
