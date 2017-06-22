/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 13:47:30 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/17 14:56:54 by ade-sede         ###   ########.fr       */
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

const char	*casual_realloc(short *error)
{
	char	*fill = "This is a test\n";
	char	*str = strdup(fill);
	char	*str_2 = strdup(fill);
	char	*realloc_ret;
	size_t	fill_len = strlen(fill);
	char	*new_part = "lol";
	size_t	new_part_len = strlen(new_part);

	str = ft_realloc(fill_len, str, new_part_len + fill_len + 1);
	strcpy(str + fill_len, new_part);
	realloc_ret = realloc(str_2, new_part_len + fill_len + 1);
	strcpy(realloc_ret + fill_len, new_part);
	printf("My str = "MAG"#"CYN"%s"MAG"#\n"RESET, str);
	printf("   str = "MAG"#"CYN"%s"MAG"#\n"RESET, realloc_ret);
	if (strcmp(str, realloc_ret) != 0)
		*error = TRUE;
	free(realloc_ret);
	free(str);
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
	f[0] = &casual_realloc;
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
	return (nb_error);
}
