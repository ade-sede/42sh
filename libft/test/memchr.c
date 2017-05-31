/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 13:12:00 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/31 13:19:26 by ade-sede         ###   ########.fr       */
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




static const char	*zero_memchr(short *error)
{
	char	*src = "/|\x12\xff\x09\0\x42\042\0\42|\\";
	int		size = 12;
	void	*ret1;
	void	*ret2;

	if (memchr(src, '\0', size) != ft_memchr(src, '\0', size))
		*error = TRUE;
	printf("%ld\n", (char*)memchr(src, '\0', size) - src);
	printf("%ld\n", (char*)ft_memchr(src, '\0', size) - src);
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
	f[0] = &zero_memchr;
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
