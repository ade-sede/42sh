/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:40:51 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/12 15:56:57 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exec.h"
#include "libft.h"
#include "printf.h"
#include "line_editing.h"
#include "history.h"
#include "completion.h"
#include "get_next_line.h"
#include "color.h"
#include "my_signal.h"

#include "failure.h"
#include <stdio.h>
#include <errno.h>

#ifdef CRASH_TEST
int	file_script(char **av, t_env *env);
#endif

#ifndef CRASH_TEST
int main()
#endif
#ifdef CRASH_TEST
int	main(int ac, char **av)
#endif
{
	extern const char	**environ;
	t_env				*env;

	if (0)
		all_signal_ign();
	env = singleton_env();
	env_load_base_env(env, environ);
	create_ternary_tree(env);
	history_load(singleton_hist(), env);
	conf_term_in();
#ifdef CRASH_TEST
	file_script(av, env);
	(void)ac;
#endif
	main_loop(env);
	env_free_env(env);
	return (0);
}
