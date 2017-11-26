/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shopt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:13:48 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "builtin.h"
#include "shopt.h"
#include <stdio.h>

struct s_shopt_mask g_shopt_mask[] =
{
	{ALLEXPORT, "allexport"},
	{SYNCOLOR, "syncolor"},
	{-1, NULL},
};

int			builtin_shopt(t_env *env, const char **argv)
{
	size_t	i;
	long	opt;

	(void)argv;
	i = 0;
	opt = env->option;
	while (i < OPTNB)
	{
		ft_dprintf(1, "%s  ", g_shopt_mask[i].string);
		ft_dprintf(1, "%s\n", opt & g_shopt_mask[i].mask ? "on" : "off");
		++i;
	}
	return (EXIT_SUCCESS);
}
