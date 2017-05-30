/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strncmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 19:32:37 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/29 19:54:16 by ade-sede         ###   ########.fr       */
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
#define		REG(x)		((x > 0) ? 1 : ((x < 0) ? -1 : 0))

static const char	*casual_4_strncmp(short *error)
{
	printf(CYN"\nLauching test %s\n"RESET, __func__);
	char	*s1 = "omg1";
	char	*s2 = "omg3                ";
	size_t	size = 100000;

	int		i1 = REG(strncmp(s1, s2, size));
	int		i2 = REG(ft_strncmp(s1, s2, size));
	printf("%d\n", i1);
	printf("%d\n", i2);
	if (i1 != i2)
		*error = TRUE;
	return (__func__);
}
static const char	*casual_3_strncmp(short *error)
{
	printf(CYN"\nLauching test %s\n"RESET, __func__);
	char	*s1 = "AA1";
	char	*s2 = "AA";

	int		i1 = REG(strncmp(s1, s2, 3));
	int		i2 = REG(ft_strncmp(s1, s2, 3));
	printf("%d\n", i1);
	printf("%d\n", i2);
	if (i1 != i2)
		*error = TRUE;
	return (__func__);
}

static const char	*casual_2_strncmp(short *error)
{
	printf(CYN"\nLauching test %s\n"RESET, __func__);
	char	*s1 = "AAAAAAAAA1";
	char	*s2 = "AAAAAAAAA2";

	int		i1 = ((strncmp(s1, s2, 3) > 0) ? 1 : ((strncmp(s1, s2, 3) < 0) ? -1 :0));
	int		i2 = ((ft_strncmp(s1, s2, 3) > 0) ? 1 : ((strncmp(s1, s2, 3) < 0) ? -1 :0));
	printf("%d\n", i1);
	printf("%d\n", i2);
	if (i1 != i2)
		*error = TRUE;
	return (__func__);
}

static const char	*casual_strncmp(short *error)
{
	printf(CYN"\nLauching test %s\n"RESET, __func__);
	char	*s1 = "AA1";
	char	*s2 = "AA";

	int		i1 = (strncmp(s1, s2, 3));
	int		i2 = (ft_strncmp(s1, s2, 3));
	printf("%d\n", i1);
	printf("%d\n", i2);
	if (i1 != i2)
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
	f[0] = &casual_strncmp;
	f[1] = &casual_2_strncmp;
	f[2] = &casual_3_strncmp;
	f[3] = &casual_4_strncmp;
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
