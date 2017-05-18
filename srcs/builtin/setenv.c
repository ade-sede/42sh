/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 18:50:24 by vcombey           #+#    #+#             */
/*   Updated: 2017/05/17 22:07:00 by etieberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <unistd.h>

int		builtin_setenv(t_env *env, const char **argv)
{
	int		eq_index;
	int		i;
	int		argc;

	argc = ft_arraylen(argv);
	if (argc == 1)
		env_print_environ((const char **)env->environ);
	i = 1;
	while (i < argc)
	{
		eq_index = ft_strichr(argv[i], '=');
		if (eq_index != -1 && eq_index != 0)
			env_add_var_from_string(env, (char*)argv[i], eq_index);
		else
			return (return_failure("usage: cp key1=value1 key2=value2 ..", NULL));
		i++;
	}
	return (0);
}
