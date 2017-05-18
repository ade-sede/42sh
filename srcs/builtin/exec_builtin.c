/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 15:47:53 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/18 15:43:20 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "builtin.h"

t_builtin g_builtin[] = 
{ 
	{"cd", &builtin_cd},
	{"exit", &builtin_exit},
	{"env", &builtin_env},
	{"unsetenv", &builtin_unsetenv},
	{"setenv", &builtin_setenv},
	{"echo", &builtin_echo}
	{NULL, NULL}
};

int		exec_builtin(t_env *env, char **av)
{
	int	i;

	i = 0;
	while (g_builtin[i].key)
	{
		if (ft_strnequ(g_builtin[i].key), av[0])
		{
			env->previous_exit = g_builtin[i].f(env, av);
			return (1);
		}
		i++;
	}
	return (0);
}
