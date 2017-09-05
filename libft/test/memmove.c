/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 20:55:15 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/26 21:24:45 by ade-sede         ###   ########.fr       */
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


static const char	*overlap_memmove2(short *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	char	dst1[0xF0];
	char	dst2[0xF0];
	char	*data = "thiß ß\xde\xad\xbe\xeftriñg will be øvérlapéd !\r\n";
	int		size = 0xF0 - 0xF;

	memset(dst1, 'A', sizeof(dst1));
	memset(dst2, 'A', sizeof(dst2));

	memcpy(dst1, data, strlen(data));
	memcpy(dst2, data, strlen(data));
	memmove(dst1, dst1 + 3, size);
	ft_memmove(dst2, dst2 + 3, size);
	if (memcmp(dst1, dst2, size))
		*error = TRUE;
	return (__func__);
}

static const char	*overlap_memmove1(short *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	char	dst1[0xF0];
	char	dst2[0xF0];
	char	*data = "thiß ß\xde\xad\xbe\xeftriñg will be øvérlapéd !\r\n";
	int		size = 0xF0 - 0xF;

	memset(dst1, 'A', sizeof(dst1));
	memset(dst2, 'A', sizeof(dst2));

	memcpy(dst1, data, strlen(data));
	memcpy(dst2, data, strlen(data));
	memmove(dst1 + 3, dst1, size);
	ft_memmove(dst2 + 3, dst2, size);
	if (memcmp(dst1, dst2, size))
		*error = TRUE;
	printf("#%s#\n", dst1);
	printf("****%s****\n", dst2);
	return (__func__);
}

int	main(void) {
	size_t nb_func = 2, index = 0;
	const char *error_list[nb_func + 1];
	short int error = FALSE, nb_error = 0;
	const char *(*f[nb_func])(short int*);
	const char	*func_ret;
	bzero(f, nb_func);
	bzero(error_list, nb_func + 1);
	f[0] = &overlap_memmove1;
	f[1] = &overlap_memmove2;
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
