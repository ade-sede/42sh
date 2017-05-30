/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 19:40:24 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/24 19:45:06 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"
#include "alloc.h"
#include "string.h"
#include <stdio.h>

static const char *exit_palloc(short int *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	printf(MAG"THIS MUST EXIT\n"RESET);
	void *str = NULL;
	str = palloc(0);
	if (!str)
		*error = TRUE;
	return (__func__);
}

static const char *casual_palloc(short int *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	void *str = NULL;

	str = palloc(10);
	if (!str)
		*error = TRUE;
	return (__func__);
}

int	main(void)
{
	size_t nb_func = 2, index = 0;
	const char *error_list[nb_func + 1];
	short int error = FALSE, nb_error = 0;
	const char *(*f[nb_func])(short int*);
	const char	*func_ret;

	bzero(f, nb_func);
	bzero(error_list, nb_func + 1);
	f[0] = &casual_palloc;
	f[1] = &exit_palloc;
	while (index < nb_func)
	{
		error = FALSE;
		func_ret = f[index](&error);
		if (error)
		{
			printf(RED"FAIL @ %s\n"RESET, func_ret);
			error_list[nb_error] = func_ret;
			nb_error++;
		}
		else
			printf(GRN"SUCCESS @ %s\n"RESET, func_ret);
		index++;
	}
	if (nb_error)
	{
		printf(MAG"Reminder of failed tests\n"RESET);
		for (int i = 0; i < nb_error; i++)
			printf("- %s\n", error_list[i]);
	}
	return (0);
}
