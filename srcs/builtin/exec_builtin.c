/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 15:47:53 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/22 18:31:27 by ade-sede         ###   ########.fr       */
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
	/* {"echo", &builtin_echo}, */
	{NULL, NULL}
};

int		exec_builtin(t_env *env, const char **argv)
{
	int	i;

	i = 0;
	while (g_builtin[i].key)
	{
		if (ft_strequ(g_builtin[i].key, argv[0]))
		{
			env->previous_exit = g_builtin[i].f(env, argv);
			return (1);
		}
		i++;
	}
	return (0);
}
