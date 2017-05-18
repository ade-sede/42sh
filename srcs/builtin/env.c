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
#include "libft/libft.h"
#include <unistd.h>

static size_t	builtin_env_options(t_env *env_cpy, char **argv)
{
	size_t		i;

	i = 1;
	while (argv[i] && argv[i][0] == '-')
	{
		if (ft_strequ(argv[i], "-i"))
			ft_free_env(env_cpy);
		else if (ft_strequ(argv[i], "-u") && argv[i + 1])
		{
			env_remove_var(env_cpy, argv[i + 1]);
			i++;
		}
		else if (argv[i][1] == '-' && !argv[i][2])
			return (i + 1);
		else
		{
			ft_free_env(env_cpy);
			return_failure("env: invalid option -", argv[i]);
			return (0);
		}
		i++;
	}
	return (i);
}

void	change_var(t_env *env_cpy, char *str)
{
	int		k;
	char	*key;
	char	*value;

	k = ft_strichr(str, '=');
	str[k] = '\0';
	key = ft_strdup(str);
	value = ft_strdup(str + k + 1);
	env_add_change(env_cpy, key, value);
	free(key);
	free(value);
}

int	builtin_env(t_env *env, char **argv)
{
	t_env		env_cpy;
	size_t		i;
	size_t		argc;
	int		exit_status;

	argc = ft_arraylen(argv);
	if (argc == 1)
	{
		env_print_environ(env->environ);
		return (0); 
	}
	env_cpy = duplicate_env(env);
	if ((i = builtin_env_options(&env, argv)) == 0)
		return (1);
	while (i < argc)
	{
		if (ft_strchri(argv[i], '=') > 0)
			change_var(env_cpy, argv[i]);
		else if (!(ft_strequ(argv[i], "env")))
		{
			exit_status = fork_exec_bin(env_cpy, argv + i);
			ft_free_env(&env_cpy);
			return (exit_status);
		}
		i++;
	}
	ft_free_env(&env_cpy);
	env_print_environ(env_cpy->environ);
}
