/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 19:53:06 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/24 20:01:33 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"
#include "mem.h"
#include "libft.h"
#include "color.h"
#include "alloc.h"
#include "string.h"
#include <stdio.h>

static const char *exit_calloc(short int *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	printf(MAG"THIS MUST EXIT\n"RESET);
	void *str = NULL;
	
	str = ft_calloc(0, 0);
	if (!str)
		*error = TRUE;
	return (__func__);
}

static const char *casual_calloc(short int *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	void *str = NULL;
	size_t str_size;

	str_size = 10;
	str = ft_calloc(sizeof(char**),str_size);
	if (!str)
		*error = TRUE;
	for (size_t r = 0; r != str_size; r++)
		if (((char*)str)[r] != 0)
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
	f[0] = &casual_calloc;
	f[1] = &exit_calloc;
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
