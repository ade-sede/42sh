/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 19:41:03 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/12 00:56:19 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "printf.h"
#include <string.h>
#include "str.h"

static const char *long_string(short int *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	const char *str;
	size_t	ft_ret = 0;
	size_t	ret = 0;

	str = "shqweeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeqweqwoehqiwuheuiqwehiqw";
	printf("ft_strlen = %zu\n", (ft_ret = ft_strlen(str)));
	printf("strlen = %zu\n", (ret = strlen(str)));
	if (ft_ret != ret)
		*error = TRUE;
	return (__func__);
}


static const char *short_string(short int *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	const char *str;
	size_t	ft_ret = 0;
	size_t	ret = 0;

	str = "sh";
	printf("ft_strlen = %zu\n", (ft_ret = ft_strlen(str)));
	printf("strlen = %zu\n", (ret = strlen(str)));
	if (ft_ret != ret)
		*error = TRUE;
	return (__func__);
}

static const char *empty_string(short int *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	const char *str;
	size_t	ft_ret = 0;
	size_t	ret = 0;

	str = "";
	printf("ft_strlen = %zu\n", (ft_ret = ft_strlen(str)));
	printf("strlen = %zu\n", (ret = strlen(str)));
	if (ft_ret != ret)
		*error = TRUE;
	return (__func__);
}

static const char *casual_string(short int *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	const char *str;
	size_t	ft_ret = 0;
	size_t	ret = 0;

	str = "0123456789";
	printf("ft_strlen = %zu\n", (ft_ret = ft_strlen(str)));
	printf("strlen = %zu\n", (ret = strlen(str)));
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
	f[0] = &casual_string;
	f[1] = &empty_string;
	f[2] = &short_string;
	f[3] = &long_string;
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
