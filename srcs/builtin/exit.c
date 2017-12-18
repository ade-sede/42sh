/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/12/18 19:28:02 by vcombey          ###   ########.fr       */
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
	if (singleton_jc()->shell_is_interactive)
		conf_term_canonical();
	exit(exit_status);
}

static	int		check_jobs(void)
{
	t_job		*j;

	j = singleton_jc()->first_job;
	while (j)
	{
		if (job_is_stopped(j) && !job_is_completed(j))
		{
			if (singleton_jc()->warn_exit == 2)
			{
				mark_job_as_done(j);
				if (kill(-j->pgid, SIGCONT) < 0)
					investigate_error(1, "kill (SIGCONT)", NULL, 0);
				kill(-j->pgid, SIGQUIT);
			}
			else if (singleton_jc()->warn_exit == 1)
				return (investigate_error(1, NULL,
				"There are stopped jobs.", 1));
			else
				return (EXIT_SUCCESS);
		}
		j = j->next;
	}
	return (EXIT_SUCCESS);
}

int				builtin_exit(t_env *env, const char **argv)
{
	int		exit_status;
	int		argc;
	char	*exit_str;

	argc = ft_arraylen(argv);
	if ((exit_status = check_jobs()))
		return (exit_status);
	if (!(exit_str = local_get_value(env->local, "?")) || \
			ft_atoi_safe(exit_str, &exit_status))
		exit_status = 1;
	if (argc == 1)
		exit_quit(exit_status);
	if (argc > 2)
		return (investigate_error(1, NULL, "exit: too many arguments", 1));
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
