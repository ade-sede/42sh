/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraydup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 10:56:38 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/11 11:09:45 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mem.h"
#include <stdio.h>
#include "alloc.h"
#include "color.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

static const char	*casual_arraydup(short *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	char	**original_array;
	char	**copy;
	size_t	size = 10;
	size_t	index = 0;

	original_array = ft_memalloc(sizeof(char*) * (size + 1));
	while (index != size)
	{
		original_array[index] = ft_itoa_base(index, 10);
		printf("%s\n", original_array[index]);
		index++;
	}
	copy = ft_arraydup((const char**)original_array);
	index = 0;
	while (index != size)
	{
		printf(MAG"#"CYN"%s"MAG"#\n"RESET, original_array[index]);
		printf(MAG"#"CYN"%s"MAG"#\n"RESET, copy[index]);
		if (strcmp(copy[index], original_array[index]) != 0)
			*error = TRUE;
		index++;
	}
	return (__func__);
}

int	main(void)
{
	size_t nb_func = 1, index = 0;
	const char *error_list[nb_func + 1];
	short int error = FALSE, nb_error = 0;
	const char *(*f[nb_func])(short int*);
	const char	*func_ret;
	bzero(f, nb_func);
	bzero(error_list, nb_func + 1);
	f[0] = &casual_arraydup;
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
		printf(MAG"\nReminder of failed tests\n"RESET);
		for (int i = 0; i < nb_error; i++)
			printf("- %s\n", error_list[i]);
	}
	return (0);
}
