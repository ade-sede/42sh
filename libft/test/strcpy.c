/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 13:23:24 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/15 12:00:34 by ade-sede         ###   ########.fr       */
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

static const char	*empty_strcpy(short *error)
{
	printf(CYN"\nLaunching test%s\n"RESET, __func__);
	char	*src = "";
	char	dst1[30];
	char	dst2[30];

	memset(dst1, 'B', sizeof(dst1));
	memset(dst2, 'B', sizeof(dst2));

	strcpy(dst1, src);
	ft_strcpy(dst2, src);
	printf("Src -> %s\n", src);
	printf("dest -> %s\n", dst1);
	printf("ft_dest -> %s\n", dst2);
	if (strcmp(dst1, dst2))
		*error = TRUE;
	return (__func__);
}

static const char	*overflow_strcpy(short *error)
{
	printf(CYN"\nLaunching test%s\n"RESET, __func__);
	char	*src = "AAAA";
	char	dst1[80];
	char	dst2[80];

	memset(dst1, 'B', sizeof(dst1));
	memset(dst2, 'B', sizeof(dst2));

	strcpy(dst1, src);
	ft_strcpy(dst2, src);
	printf("Src -> %s\n", src);
	printf("dest -> %s\n", dst1);
	printf("ft_dest -> %s\n", dst2);
	if (memcmp(dst1, dst2, 20)) 
		*error = TRUE;
	return (__func__);
}
static const char	*basic_strcpy(short *error)
{
	printf(CYN"\nLaunching test%s\n"RESET, __func__);
	char	*src = "--> nyancat <--\n\r";
	char	dst1[30];
	char	dst2[30];

	memset(dst1, 'A', sizeof(dst1));
	memset(dst2, 'A', sizeof(dst2));

	strcpy(dst1, src);
	ft_strcpy(dst2, src);
	printf("Src -> %s\n", src);
	printf("dest -> %s\n", dst1);
	printf("ft_dest -> %s\n", dst2);
	if (strcmp(dst1, dst2))
		*error = TRUE;
	return (__func__);
}
static const char	*casual_strcpy(short *error)
{
	printf(CYN"\nLaunching test%s\n"RESET, __func__);
	const char *src;
	char	*dst;
	size_t	src_size = 10;

	src = strndup("This is a test stringqwe qwe qwe qwe qew ", src_size);
	dst = malloc(sizeof(*dst) * (src_size + 1));
	printf("Source -> %s#END\n", src);
	if (ft_strcpy(dst, src) != dst)
		*error = TRUE;
	printf("Dest -> %s\n", dst);
	if (strcmp(dst, src) != 0)
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
	f[0] = casual_strcpy;
	f[1] = basic_strcpy;
	f[2] = overflow_strcpy;
	f[3] = empty_strcpy;
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
