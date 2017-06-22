/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 14:41:21 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/12 14:46:46 by ade-sede         ###   ########.fr       */
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


const char	*nul_strrstr(short *error)
{
	const char	*big;
	const char	*little;
	char	*ret;

	big = "AbAbAbAbAb";
	little = "yop";
	ret = ft_strrstr(big, little);
	printf("%s\n", ret);
	if (ret != NULL)
		*error = TRUE;
	return (__func__);
}

const char	*casual_strrstr(short *error)
{
	const char	*big;
	const char	*little;
	char	*ret;

	big = "AbAbAbAbAb";
	little = "Ab";
	ret = ft_strrstr(big, little);
	printf("%s\n", ret);
	if (ret - big != 8)
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
	f[0] = &casual_strrstr;
	f[1] = &nul_strrstr;
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
