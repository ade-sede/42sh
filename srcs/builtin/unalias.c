/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unalias.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:46 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:05 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "builtin.h"
#include "libft.h"
#include "printf.h"

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
