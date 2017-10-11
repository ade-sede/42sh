/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:40:51 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/11 22:41:00 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <unistd.h>
#include "failure.h"

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
		{
			env_add_var_from_string(env, (char*)argv[i], eq_index);
			if (ft_strnequ(argv[i], "PATH", 4))
				env_reload_tree_hash(env);
		}
		else
		{
			return (investigate_error(1, NULL, "usage: setenv key1=value1 \
key2=value2 ..", EXIT_FAILURE));
		}
		i++;
	}
	return (0);
}
