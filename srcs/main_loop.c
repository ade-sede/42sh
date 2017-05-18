/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <vcombey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 15:01:19 by vcombey           #+#    #+#             */
/*   Updated: 2017/05/16 15:27:53 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include "env.h"

void	exec(t_env *env, char **argv)
{
	if (!(exec_builtin(argv)))
		ft_fork_exec(argv, *env, previous_exit);
}

void	put_prompt(t_env *env)
{
	(void)env;

	ft_putstr("$>");
}

void	ft_sh(t_env *env)
{
	char		*line;
	char		**argv;

	put_prompt(env);
	while (42)
	{
		//refresh_buff_and_history();
		//line = get_input(env);
		line = get_next_line(0, &line);
		argv = ft_strsplit(line, " \t");
		exec(env, &previous_exit);
		put_prompt(env);
		ft_arraydel(&argv);
	}
}

/*
void		exit_proper(int signum)
{
	conf_term_out();
	(void)signum;
	exit(1);
}

void	set_signals(void)
{
	signal(SIGHUP, exit_proper);
	//signal(SIGWINCH, refresh_screen);
	//signal(SIGCONT, restart);
	//signal(SIGTSTP, suspend);
	signal(SIGINT, exit_proper);
	signal(SIGTERM, exit_proper);
	signal(SIGQUIT, exit_proper);
	signal(SIGFPE, exit_proper);
	signal(SIGKILL, exit_proper);
}*/
