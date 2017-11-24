/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:13:45 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_env.h"
#include "environ.h"
#include "printf.h"
#include "local.h"

#include <stdio.h>

static int	treat_string(t_env *env, const char *argv)
{
	ssize_t	eq_pos;
	char	*local_value;

	eq_pos = ft_strichr(argv, '=');
	if (eq_pos == -1)
	{
		local_value = local_get_value(env->local, argv);
		if (local_value)
			env_add_change(env, argv, (const char*)local_value);
	}
	else
		env_add_var_from_string(env, (char*)argv, eq_pos);
	return (1);
}

int			builtin_export(t_env *env, const char **argv)
{
	size_t	len;
	size_t	i;

	i = 1;
	len = ft_arraylen(argv);
	if (len == 1 || (len > 1 && ft_strequ(argv[1], "-p")))
	{
		env_print_environ((const char**)env->environ);
		return (EXIT_SUCCESS);
	}
	while (i != len)
	{
		if (*argv[i] == '-' && !ft_strequ(argv[i], "-p"))
		{
			ft_dprintf(2, "Wrong option %s\n", argv[i]);
			return (EXIT_FAILURE);
		}
		if (!treat_string(env, argv[i]))
			return (EXIT_FAILURE);
		++i;
	}
	return (EXIT_FAILURE);
}
