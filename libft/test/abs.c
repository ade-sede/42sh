/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 15:12:58 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/24 19:45:05 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include "printf.h"


static const char *UINT64max(short int *error)
{
	printf(CYN"\nRunning test %s\n"RESET, __func__);
	intmax_t	abs_UINT64max = ft_abs(UINT64_MAX);
	intmax_t	abs_UINT64min = ft_abs(-(UINT64_MAX));
	printf("ABS of UINT64_MAX = %jd\n", abs_UINT64max);
	printf("ABS of UINT64_MAX = %jd\n", abs_UINT64min);
	if (abs_UINT64max != abs_UINT64min)
		*error = TRUE;
	return (__func__);
}

static const char *INT8max(short int *error)
{
	printf(CYN"\nRunning test %s\n"RESET, __func__);
	intmax_t	abs_INT8max = ft_abs(INT8_MAX);
	intmax_t	abs_INT8min = ft_abs(-(INT8_MAX));
	printf("ABS of INT8_MAX = %jd\n", abs_INT8max);
	printf("ABS of INT8_MAX = %jd\n", abs_INT8min);
	if (abs_INT8max != abs_INT8min)
		*error = TRUE;
	return (__func__);
}

static const char *INT16max(short int *error)
{
	printf(CYN"\nRunning test %s\n"RESET, __func__);
	intmax_t	abs_INT16max = ft_abs(INT16_MAX);
	intmax_t	abs_INT16min = ft_abs(-(INT16_MAX));
	printf("ABS of INT16_MAX = %jd\n", abs_INT16max);
	printf("ABS of INT16_MAX = %jd\n", abs_INT16min);
	if (abs_INT16max != abs_INT16min)
		*error = TRUE;
	return (__func__);
}

static const char *INT32max(short int *error)
{
	printf(CYN"\nRunning test %s\n"RESET, __func__);
	intmax_t	abs_INT32max = ft_abs(INT32_MAX);
	intmax_t	abs_INT32min = ft_abs(-(INT32_MAX));
	printf("ABS of INT32_MAX = %jd\n", abs_INT32max);
	printf("ABS of INT32_MAX = %jd\n", abs_INT32min);
	if (abs_INT32max != abs_INT32min)
		*error = TRUE;
	return (__func__);
}

static const char *INT64max(short int *error)
{
	printf(CYN"\nRunning test %s\n"RESET, __func__);
	intmax_t	abs_INT64max = ft_abs(INT64_MAX);
	intmax_t	abs_INT64min = ft_abs(-(INT64_MAX));
	printf("ABS of INT64_MAX = %jd\n", abs_INT64max);
	printf("ABS of INT64_MAX = %jd\n", abs_INT64min);
	if (abs_INT64max != abs_INT64min)
		*error = TRUE;
	return (__func__);
}

int	main(void)
{
	size_t nb_func = 5, index = 0;
	const char *error_list[nb_func + 1];
	short int error = FALSE, nb_error = 0;
	const char *(*f[nb_func])(short int*);
	const char	*func_ret;

	bzero(f, nb_func);
	bzero(error_list, nb_func + 1);
	f[0] = &INT64max;
	f[1] = &INT32max;
	f[2] = &INT16max;
	f[3] = &INT8max;
	f[4] = &UINT64max;
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
