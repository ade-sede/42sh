/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unalias.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 00:27:15 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/16 00:27:19 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "builtin.h"
#include "libft.h"
#include "printf.h"
#include <stdio.h>

int			builtin_unalias(t_env *env, const char **argv)
{
	int		argc;
	int		i;
	t_list	*node;
	int		ret;

	i = 0;
	ret = EXIT_SUCCESS;
	argc = ft_arraylen(argv);
	if (argc == 1)
		return (return_failure(NULL, "unalias : Argument required"));
	while (++i < argc)
	{
		node = find_alias(env->alias, argv[i], ft_strlen(argv[i]));
		if (node)
		{
			ft_simple_lst_del_one(&env->alias, node, ft_free);
			ret = EXIT_SUCCESS;
		}
		else
		{
			return_failure("alias not found : ", argv[i]);
			ret = EXIT_FAILURE;
		}
	}
	return (ret);
}
