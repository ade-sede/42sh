/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 00:11:36 by vcombey           #+#    #+#             */
/*   Updated: 2017/05/17 16:34:31 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include <unistd.h>

int		ft_env_option(t_env **env, char **argv)
{
	int		i;

	i = 1;
	while (argv[i] && argv[i][0] == '-')
	{
		if (ft_strequ(argv[i], "-i"))
			ft_free_env(env);
		else if (ft_strequ(argv[i], "-u") && argv[i + 1])
		{
			ft_delete_var(env, argv[i + 1]);
			i++;
		}
		else if (argv[i][1] == '-' && !argv[i][2])
			return (i + 1);
		else
		{
			ft_free_env(env);
			ft_return_err("env: invalid option -", argv[i]);
			return (0);
		}
		i++;
	}
	return (i);
}

void	change_var(char *str, t_env **env)
{
	int		k;
	char	*var;
	char	*value;

	k = ft_strchri(str, '=');
	str[k] = '\0';
	var = ft_strdup(str);
	value = ft_strdup(str + k + 1);
	if (!(ft_change_var(*env, var, value)))
		ft_envadd(ft_envnew(var, value), env);
}

void	display_environ(char **environ)
{
	ft_putstrstr(environ);
	tab_free(environ);
	return ;
}

void	display_new_environ(t_env *env)
{
	char	**new_environ;

	new_environ = ft_lsttotab(env);
	ft_putstrstr(new_environ);
	tab_free(new_environ);
	if (env != NULL)
		ft_free_env(&env);
}

void	ft_env(char **argv, char *line, char **environ, int *previous_exit)
{
	t_env	*env;
	int		i;

	if (ft_strstrlen(argv) == 1)
		return (display_environ(environ));
	env = ft_tabtolst(environ);
	tab_free(environ);
	if ((i = ft_env_option(&env, argv)) == 0)
		return ;
	while (argv[i])
	{
		if (ft_strchri(argv[i], '=') > 0)
			change_var(argv[i], &env);
		else if (!(ft_strequ(argv[i], "env")))
		{
			ft_parse(argv + i, line, &env, previous_exit);
			ft_free_env(&env);
			return ;
		}
		i++;
	}
	display_new_environ(env);
}
