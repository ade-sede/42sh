/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:13:45 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_env.h"
#include "local.h"
#include "builtin.h"
#include "failure.h"
#include "history.h"

#include "job_control.h"
static void		exit_quit(int exit_status)
{
	history_write_to_histfile();
	if (isatty(STDIN_FILENO))
		conf_term_canonical();
	exit(exit_status);
}

int				builtin_exit(t_env *env, const char **argv)
{
	int		exit_status;
	int		argc;
	t_job		*j;

	argc = ft_arraylen(argv);
	j = singleton_jc()->first_job;
	while (j)
	{
		if(job_is_stopped(j) && !job_is_completed(j))
			return (investigate_error(1, NULL, "There are stopped"
			" jobs.",1));
		j = j->next;
	}

	// End BG PROCESS
	if (!ft_atoi_safe(local_get_value(env->local, "?"), &exit_status))
		exit_status = 1;
	if (argc == 1)
		exit_quit(exit_status);
	if (argc > 2)
		return (investigate_error(1, NULL, "exit: too many arguments",
					EXIT_FAILURE));
	else if (!(ft_atoi_safe(argv[1], &exit_status)))
	{
		history_write_to_histfile();
		if (isatty(STDIN_FILENO))
			conf_term_canonical();
		exit(investigate_error(1, "exit: numeric argument required", argv[1],
					255));
	}
	else
		exit_quit(exit_status);
	return (EXIT_SUCCESS);
}
