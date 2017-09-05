/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strrchr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 12:20:49 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/26 12:22:38 by ade-sede         ###   ########.fr       */
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


static const char	*big_null_strrchr(short *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	const char	*str = "Here comes a . Here it i heqw oiojeq wjowqej oiwqje oiqwje oqhe iuwqhe iuwqhe iuwq es";
	if (ft_strrchr(str, '0') != strrchr(str, '0'))
		*error = TRUE;
	return (__func__);
}

static const char	*big_strrchr(short *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	const char	*str = "Here comes a heqwiuheiuwqheiuwqhe iuqwhe iuhewq iuwqhe iuqhwe ewiwqe iuwqhe iuwqe hiwque qe 0. Here it is";
	if (ft_strrchr(str, '0') != strrchr(str, '0'))
		*error = TRUE;
	printf("%c\n", *ft_strrchr(str, '0'));
	if (*ft_strrchr(str, '0') != '0')
		*error = TRUE;
	return (__func__);
}

static const char	*null_strrchr(short *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	const char	*str = "Here comes a . Here it is";
	if (ft_strrchr(str, '0') != strrchr(str, '0'))
		*error = TRUE;
	return (__func__);
}

static const char	*casual_strrchr(short *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	const char	*str = "Here comes a 0. Here it is";
	if (ft_strrchr(str, '0') != strrchr(str, '0'))
		*error = TRUE;
	printf("%c\n", *ft_strrchr(str, '0'));
	if (*ft_strrchr(str, '0') != '0')
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
	f[0] = &casual_strrchr;
	f[1] = &big_strrchr;
	f[2] = &null_strrchr;
	f[3] = &big_null_strrchr;
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
