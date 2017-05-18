/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 18:50:24 by vcombey           #+#    #+#             */
/*   Updated: 2017/05/18 15:03:01 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft/libft.h"
#include <unistd.h>

void	ft_setenv(char **argv, t_env **env)
{
	int		k;
	char	*var;
	char	*value;
	char	**environ;

	if (ft_strstrlen(argv) == 1)
	{
		environ = ft_lsttotab(*env);
		ft_putstrstr(environ);
	}
	else if (ft_strstrlen(argv) > 2)
		ft_putstr_fd("setenv: Too many arguments\n", 2);
	else if ((k = ft_strchri(argv[1], '=')) > 0)
	{
		argv[1][k] = '\0';
		var = ft_strdup(argv[1]);
		value = ft_strdup(argv[1] + k + 1);
		if (!(ft_change_var(*env, var, value)))
			ft_envadd(ft_envnew(var, value), env);
	}
	else
		ft_putstr_fd("usage: setenv VAR=value\n", 2);
}
