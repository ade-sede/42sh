/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:40:51 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/11 22:41:00 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "builtin.h"
#include "local.h"

int		builtin_unset(t_env *env, const char **argv)
{
	size_t	x;

	if (ft_arraylen(argv) == 1)
		return (EXIT_FAILURE);
	x = 1;
	while (argv[x] != NULL)
	{
		if (!env->local)
			break ;
		remove_var_from_local(&env->local, (char*)argv[x]);
		x++;
	}
	return (EXIT_SUCCESS);
}
