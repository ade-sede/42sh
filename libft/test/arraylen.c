/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 18:44:18 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/24 19:45:05 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "printf.h"


static const char *null_array(short int *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	printf(MAG"THIS MUST SEGV\n");
	char **array = NULL;
	size_t	ft_ret;
	size_t	ret = 0;

	ft_ret = ft_arraylen((const char **)array);
	printf("ft_ret = %zu\n", ft_ret);
	printf("Ret = %zu\n", ret);
	if (ft_ret != ret)
		*error = TRUE;
	return (__func__);
}

static const char *not_null_terminated_array(short int *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	char *array[] = {"lol", "lol"};
	size_t	ft_ret;
	size_t	ret = 2;

	ft_ret = ft_arraylen((const char **)array);
	printf("ft_ret = %zu\n", ft_ret);
	printf("Ret = %zu\n", ret);
	if (ft_ret != ret)
		*error = TRUE;
	return (__func__);
}

static const char *empty_array(short int *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	char *array[] = {NULL};
	size_t	ft_ret;
	size_t	ret = 0;

	ft_ret = ft_arraylen((const char **)array);
	printf("ft_ret = %zu\n", ft_ret);
	printf("Ret = %zu\n", ret);
	if (ft_ret != ret)
		*error = TRUE;
	return (__func__);
}

static const char *casual_array(short int *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	char *array[] = {"LOL", "LOL", NULL};
	size_t	ft_ret;
	size_t	ret = 2;

	ft_ret = ft_arraylen((const char **)array);
	printf("ft_ret = %zu\n", ft_ret);
	printf("Ret = %zu\n", ret);
	if (ft_ret != ret)
		*error = TRUE;
	return (__func__);
}

int	main(void)
{
	size_t nb_func = 4, index = 0;
	const char *error_list[nb_func + 1];
	short int error = FALSE, nb_error = 0;
	const char *(*f[nb_func])(short int*);
	const char	*func_ret;

	bzero(f, nb_func);
	bzero(error_list, nb_func + 1);
	f[0] = &casual_array;
	f[1] = &empty_array;
	f[2] = &not_null_terminated_array;
	f[3] = &null_array;
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
