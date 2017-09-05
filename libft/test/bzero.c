/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bzero.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 12:47:06 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/24 19:52:04 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include "mem.h"
#include <stdio.h>
#include "alloc.h"
#include "printf.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

static const char *border_bzero(short int *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	char	*str;
	size_t str_size = 58;
	size_t bzero_start = str_size - 1;
	size_t bzero_size = 1;

	str = palloc(sizeof(char*) * (str_size + 1));
	str[str_size] = 0;
	memset(str, 48, str_size);
	printf("The next line should contain %zu '0'\n", str_size);
	printf("%s\n", str);
	bzero(str + bzero_start, bzero_size);
	printf("The next line should contain %zu '0'\n", (bzero_size) ? bzero_start : str_size);
	printf("%s\n", str);
	if (str[0] != '0')
		*error = TRUE;
	if (bzero_start + bzero_size != str_size)
		if (str[bzero_start + bzero_size] != '0')
			*error = TRUE;
	for (size_t t = 0; t != bzero_start; t++)
		if (str[t] != '0')
			*error = TRUE;
	for (size_t r = bzero_start; r != bzero_start + bzero_size; r++)
		if (str[r] != 0)
			*error = TRUE;
	return (__func__);
}

static const char *big_bzero(short int *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	char	*str;
	size_t str_size = 57;
	size_t bzero_start = 1;
	size_t bzero_size = str_size - bzero_start - 1;
	clock_t start1, stop1, start2, stop2;

	str = palloc(sizeof(char*) * (str_size + 1));
	str[str_size] = 0;
	memset(str, 48, str_size);
	printf("The next line should contain %zu '0'\n", str_size);
	printf("%s\n", str);
	bzero(str + bzero_start, bzero_size);
	printf("The next line should contain %zu '0'\n", (bzero_size) ? bzero_start : str_size);
	printf("%s\n", str);
	if (str[0] != '0')
		*error = TRUE;
	if (bzero_start + bzero_size != str_size)
		if (str[bzero_start + bzero_size] != '0')
			*error = TRUE;
	for (size_t t = 0; t != bzero_start; t++)
		if (str[t] != '0')
			*error = TRUE;
	for (size_t r = bzero_start; r != bzero_start + bzero_size; r++)
		if (str[r] != 0)
			*error = TRUE;
	return (__func__);
}

static const char *zero_bzero(short int *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	char	*str;
	size_t str_size = 10;
	size_t bzero_start = 0;
	size_t bzero_size = 0;

	str = palloc(sizeof(char*) * (str_size + 1));
	str[str_size] = 0;
	memset(str, 48, str_size);
	printf("The next line should contain %zu '0'\n", str_size);
	printf("%s\n", str);
	ft_bzero(str + bzero_start, bzero_size);
	printf("The next line should contain %zu '0'\n", (bzero_size) ? bzero_start : str_size);
	printf("%s\n", str);
	if (str[0] != '0')
		*error = TRUE;
	if (bzero_start + bzero_size != str_size)
		if (str[bzero_start + bzero_size] != '0')
			*error = TRUE;
	for (size_t t = 0; t != bzero_start; t++)
		if (str[t] != '0')
			*error = TRUE;
	for (size_t r = bzero_start; r != bzero_start + bzero_size; r++)
		if (str[r] != 0)
			*error = TRUE;
	return (__func__);
}

static const char *bzero_inline_bzero(short int *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	char	*str;
	size_t str_size = 10;
	size_t bzero_start = 2;
	size_t bzero_size = 4;

	str = palloc(sizeof(char*) * (str_size + 1));
	str[str_size] = 0;
	memset(str, 48, str_size);
	printf("The next line should contain %zu '0'\n", str_size);
	printf("%s\n", str);
	ft_bzero(str + bzero_start, bzero_size);
	printf("The next line should contain %zu '0'\n", (bzero_size) ? bzero_start : str_size);
	printf("%s\n", str);
	if (bzero_start + bzero_size != str_size)
		if (str[bzero_start + bzero_size] != '0')
			*error = TRUE;
	for (size_t t = 0; t != bzero_start; t++)
		if (str[t] != '0')
			*error = TRUE;
	for (size_t r = bzero_start; r != bzero_start + bzero_size; r++)
		if (str[r] != 0)
			*error = TRUE;
	return (__func__);
}


static const char *casual_bzero(short int *error)
{

	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	char	*str;
	size_t str_size = 10;
	size_t bzero_start = str_size - 2;
	size_t bzero_size = 1;

	str = palloc(sizeof(char*) * (str_size + 1));
	str[str_size] = 0;
	memset(str, 48, str_size);
	printf("The next line should contain %zu '0'\n", str_size);
	printf("%s\n", str);
	ft_bzero(str + bzero_start, bzero_size);
	printf("The next line should contain %zu '0'\n", (bzero_size) ? bzero_start : str_size);
	printf("%s\n", str);
	if (bzero_start + bzero_size != str_size)
		if (str[bzero_start + bzero_size] != '0')
			*error = TRUE;
	for (size_t t = 0; t != bzero_start; t++)
		if (str[t] != '0')
			*error = TRUE;
	for (size_t r = bzero_start; r != bzero_start + bzero_size; r++)
		if (str[r] != 0)
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
	f[0] = &casual_bzero;
	f[1] = &bzero_inline_bzero;
	f[2] = &zero_bzero;
	f[3] = &big_bzero;
	f[4] = &border_bzero;
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
