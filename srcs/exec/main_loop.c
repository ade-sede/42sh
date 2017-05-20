/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <vcombey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 15:01:19 by vcombey           #+#    #+#             */
/*   Updated: 2017/05/20 20:02:39 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include "env.h"
#include "exec.h"
#include "builtin.h"

void	exec(t_env *env, const char **argv)
{
	if (!(exec_builtin(env, argv)))
		fork_exec_bin(env, argv);
}

void	put_prompt(t_env *env)
{
	(void)env;

	ft_putstr("$>");
}

void	main_loop(t_env *env)
{
	char		**argv;
	char		buf[4096];

	put_prompt(env);
	while (42)
	{
		//refresh_buff_and_history();
		//line = get_input(env);
		ft_bzero(buf, 4096);
		read(0, buf, 4096);
		*ft_strchr(buf, '\n') = '\0';
		argv = ft_strsplit_quotes(buf, " \t");
		exec(env, (const char **)argv);
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
