/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:13:48 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "local.h"

int		builtin_unset(t_env *env, const char **argv)
{
	size_t	x;

	if (ft_arraylen(argv) == 1)
		return (EXIT_FAILURE);
	x = 1;
	while (argv[x] && env->local)
	{
		local_remove(env, argv[x]);
		++x;
	}
	return (EXIT_SUCCESS);
}
