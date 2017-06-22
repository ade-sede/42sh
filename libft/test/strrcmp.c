/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strrcmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 15:32:57 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/12 16:21:20 by ade-sede         ###   ########.fr       */
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
#include "str.h"



const char	*small_strrcmp(short *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	const char	*s1 = ".";
	const char	*s2 = "..";
	printf("%d\n", ft_strrcmp(s1, s2));
	if (ft_strrcmp(s1, s2) == 0)
		*error = TRUE;
	return (__func__);
}

const char	*path_strrcmp(short *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	const char	*s1 = "./.";
	const char	*s2 = "..";
	printf("%d\n", ft_strrcmp(s1, s2));
	if (ft_strrcmp(s1, s2) == 0)
		*error = TRUE;
	return (__func__);
}

const char	*wrong_strrcmp(short *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	const char	*s1 = "This should return !0";
	const char	*s2 = "lol";
	printf("%d\n", ft_strrcmp(s1, s2));
	if (ft_strrcmp(s1, s2) == 0)
		*error = TRUE;
	return (__func__);
}

const char	*casual_strrcmp(short *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	const char	*s1 = "This should return 0. lol";
	const char	*s2 = "lol";
	printf("%d\n", ft_strrcmp(s1, s2));
	if (ft_strrcmp(s1, s2) != 0)
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
	f[0] = &casual_strrcmp;
	f[1] = &wrong_strrcmp;
	f[2] = &path_strrcmp;
	f[3] = &small_strrcmp;
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

