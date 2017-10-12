/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:40:51 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/11 22:41:00 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local.h"
#include "builtin.h"
#include "option.h"

static void		print_t_option_id(t_option_id id)
{
	if (id == ALLEXPORT)
		write(1, "allexport  ", 11);
	else if (id == INTERACTIVE)
		write(1, "interactive", 11);
	else
		write(1, "unknown    ", 11);
}

void			print_all_option(t_env *env)
{
	int			x;
	long		mask;

	x = 0;
	mask = 1;
	while (x < 31)
	{
		print_t_option_id(mask);
		write(1, "\t\n", 1);
		write(1, (((env->option & mask) == mask) ? "on\n" : "off\n"),
				(((env->option & mask) == mask) ? 3 : 4));
		mask = mask << 1;
		x++;
	}
}

void			print_current_option(t_env *env)
{
	int		x;
	long	mask;

	x = 0;
	mask = 1;
	while (x < 31)
	{
		if (((env->option & mask) == mask))
		{
			write(1, "set -o ", 7);
			print_t_option_id(mask);
			write(1, "\n", 1);
		}
		mask = mask << 1;
		x++;
	}
}

int				match_name_option(const char *argv)
{
	if (strcmp("allexport", argv) == 0)
		return (ALLEXPORT);
	else if (strcmp("interactive", argv) == 0)
		return (INTERACTIVE);
	else
		return (-1);
}
