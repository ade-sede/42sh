/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 15:47:53 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/18 15:03:01 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include <stdio.h>

static int	builtin_cd(t_env *env, char **argv)
{
	(void)(env);
	printf("%s\n", *++argv);
	return (1);
}

typedef struct	s_builtin
{
	const char	*key;
	int		(*f)(t_env*, char**);
}			t_builtin;


t_builtin g_builtin[] = 
{ 
			{"cd", &builtin_cd},
			{"pwd", &builtin_pwd}
};

int		main(int ac, char *av[])
{
	printf("%s\n", g_builtin[0].key);
	if (ac == 2)
		g_builtin[0].f(NULL, av);
	return (0);
}
