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

static const char	**apply_opt(t_env *env, const char **argv, int	*error)
{
	while (*argv)
	{
		if (ft_strequ(*argv, "-i"))
		{
			env_free_env(env);
			env->environ = env_create_environ(NULL, NULL);
			argv++;
		}
		else if (ft_strequ(*argv, "-u"))
		{
			if (!(*(argv + 1)))
			{
				return_failure("env: option requires an argument -- u\n", NULL);		
				*error = 1;
				return (argv);
			}
			env_remove_var(env, *(argv + 1));
			argv += 2;
		}
		else if (ft_strequ(*argv, "-"))
			argv++;
		else if (ft_strequ(*argv, "--"))
			return (argv + 1);
		else
			return (argv);
	}
	return (argv);
}

static const char	**build_new_env(t_env *env, const char **argv, int *error)
{
	int	eq_index;

	argv = apply_opt(env, argv, error);
	if (*error)
		return (argv);
	while (*argv)
	{
		eq_index = ft_strichr(*argv, '=');
		if (eq_index == 0)
		{
			*error = 1;
			return_failure("env: invalid argument", *argv);
			return (argv);
		}
		else if (eq_index > 0)
			env_add_var_from_string(env, (char *)*argv, eq_index);
		else
			return (argv);
		argv++;
	}
	return (argv);
}

int	builtin_env(t_env *old_env, const char **argv)
{
	t_env	new_env;
	int	error;

	error = 0;
	if (!env_copy_env(&new_env, old_env))
		return (EXIT_FAILURE);
	argv = build_new_env(&new_env, argv + 1, &error);
	if (error)
		return (EXIT_FAILURE);
	if (!(*argv))
		env_print_environ((const char**)new_env.environ);
	else
		fork_exec_bin(&new_env, argv);
	//env_free_env(&new_env);
	return (EXIT_SUCCESS);
}
