/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 00:11:36 by vcombey           #+#    #+#             */
/*   Updated: 2017/05/18 15:57:57 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exec.h"
#include "libft.h"

static size_t	builtin_env_options(t_env *env_cpy, const char **argv)
{
	size_t		i;

	i = 1;
	while (argv[i] && argv[i][0] == '-')
	{
		if (ft_strequ(argv[i], "-i"))
			env_free_env(env_cpy);
		else if (ft_strequ(argv[i], "-u") && argv[i + 1])
		{
			env_remove_var(env_cpy, argv[i + 1]);
			i++;
		}
		else if (argv[i][1] == '-' && !argv[i][2])
			return (i + 1);
		else
		{
			env_free_env(env_cpy);
			return_failure("env: invalid option -", argv[i]);
			return (0);
		}
		i++;
	}
	return (i);
}

int	builtin_env(t_env *env, const char **argv)
{
	t_env		env_cpy;
	ssize_t		eq_index;
	size_t		i;
	size_t		argc;
	int		exit_status;

	argc = ft_arraylen(argv);
	if (argc == 1)
	{
		env_print_environ((const char **)env->environ);
		return (0); 
	}
	env_copy_env(&env_cpy, env);
	if ((i = builtin_env_options(&env_cpy, argv)) == 0)
		return (1);
	while (i < argc)
	{
		eq_index = ft_strichr(argv[i], '=');
		if ( eq_index != -1 && eq_index != 0)
			env_add_var_from_string(env, (char*)argv[0], eq_index);
		else if (!(ft_strequ(argv[i], "env")))
		{
			exit_status = fork_exec_bin(&env_cpy, argv + i);
			env_free_env(&env_cpy);
			return (exit_status);
		}
		i++;
	}
	env_free_env(&env_cpy);
	env_print_environ((const char**)env_cpy.environ);
	return (EXIT_SUCCESS);
}
