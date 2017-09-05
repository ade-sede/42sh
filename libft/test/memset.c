/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 16:46:31 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/26 14:34:29 by ade-sede         ###   ########.fr       */
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


static const char	*return_memset(short *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	const int	size = 18;
	char		b1[size];

	memset(b1, 'B', size);

	char	*r1 = memset(b1, 'A', size);
	char	*r2 = ft_memset(b1, 'A', size);

	if (r1 != r2)
		*error = TRUE;

	r1 = memset("", 'A', 0);
	r2 = ft_memset("", 'A', 0);
	if (r1 != r2)
		*error = TRUE;
	return (__func__);
}
static const char *little_memset(short int *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	char	*str;
	size_t	str_size = 48;
	size_t	memset_start = 10;
	size_t	memset_size = 1;
	int		memset_value = 'u';
	int		filler = 48;

	str = palloc(sizeof(char*) * (str_size + 1));
	str[str_size] = 0;
	memset(str, 48, str_size);
	printf("The next line should contain %zu '%c' and %zu '%c'\n", str_size, filler, (size_t)0 , memset_value);
	printf("%s\n", str);
	ft_memset(str + memset_start, memset_value, memset_size);
	printf("The next line should start with %zu '%c' followed by %zu '%c'\n", (memset_size) ? memset_start : str_size, filler, memset_size, memset_value);
	printf("%s\n", str);
	if (memset_start + memset_size != str_size)
		if (str[memset_start + memset_size] != filler)
			*error = TRUE;
	for (size_t t = 0; t != memset_start; t++)
		if (str[t] != filler)
			*error = TRUE;
	for (size_t r = memset_start; r != memset_start + memset_size; r++)
		if (str[r] != memset_value)
			*error = TRUE;
	return (__func__);
}

static const char *empty_memset(short int *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	char	*str;
	size_t	str_size = 230;
	size_t	memset_start = str_size - 140;
	size_t	memset_size = 0;
	int		memset_value = 'u';
	int		filler = 48;

	str = palloc(sizeof(char*) * (str_size + 1));
	str[str_size] = 0;
	memset(str, 48, str_size);
	printf("The next line should contain %zu '%c' and %zu '%c'\n", str_size, filler, (size_t)0 , memset_value);
	printf("%s\n", str);
	ft_memset(str + memset_start, memset_value, memset_size);
	printf("The next line should start with %zu '%c' followed by %zu '%c'\n", (memset_size) ? memset_start : str_size, filler, memset_size, memset_value);
	printf("%s\n", str);
	if (memset_start + memset_size != str_size)
		if (str[memset_start + memset_size] != filler)
			*error = TRUE;
	for (size_t t = 0; t != memset_start; t++)
		if (str[t] != filler)
			*error = TRUE;
	for (size_t r = memset_start; r != memset_start + memset_size; r++)
		if (str[r] != memset_value)
			*error = TRUE;
	return (__func__);
}

static const char *big_memset(short int *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	char	*str;
	size_t	str_size = 230;
	size_t	memset_start = 5;
	size_t	memset_size = 115;
	int		memset_value = 'u';
	int		filler = 48;

	str = palloc(sizeof(char*) * (str_size + 1));
	str[str_size] = 0;
	memset(str, 48, str_size);
	printf("The next line should contain %zu '%c' and %zu '%c'\n", str_size, filler, (size_t)0 , memset_value);
	printf("%s\n", str);
	ft_memset(str + memset_start, memset_value, memset_size);
	printf("The next line should start with %zu '%c' followed by %zu '%c'\n", (memset_size) ? memset_start : str_size, filler, memset_size, memset_value);
	printf("%s\n", str);
	if (memset_start + memset_size != str_size)
		if (str[memset_start + memset_size] != filler)
			*error = TRUE;
	for (size_t t = 0; t != memset_start; t++)
		if (str[t] != filler)
			*error = TRUE;
	for (size_t r = memset_start; r != memset_start + memset_size; r++)
		if (str[r] != memset_value)
			*error = TRUE;
	return (__func__);
}

static const char *border_memset(short int *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	char	*str;
	size_t	str_size = 10;
	size_t	memset_start = 9;
	size_t	memset_size = 1;
	int		memset_value = 'u';
	int		filler = 48;

	str = palloc(sizeof(char*) * (str_size + 1));
	str[str_size] = 0;
	memset(str, 48, str_size);
	printf("The next line should contain %zu '%c' and %zu '%c'\n", str_size, filler, (size_t)0 , memset_value);
	printf("%s\n", str);
	ft_memset(str + memset_start, memset_value, memset_size);
	printf("The next line should start with %zu '%c' followed by %zu '%c'\n", (memset_size) ? memset_start : str_size, filler, memset_size, memset_value);
	printf("%s\n", str);
	if (memset_start + memset_size != str_size)
		if (str[memset_start + memset_size] != filler)
			*error = TRUE;
	for (size_t t = 0; t != memset_start; t++)
		if (str[t] != filler)
			*error = TRUE;
	for (size_t r = memset_start; r != memset_start + memset_size; r++)
		if (str[r] != memset_value)
			*error = TRUE;
	return (__func__);
}

static const char *casual_memset(short int *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	char	*str;
	size_t	str_size = 10;
	size_t	memset_start = str_size - 2;
	size_t	memset_size = 1;
	int		memset_value = 'u';
	int		filler = 48;

	str = palloc(sizeof(char*) * (str_size + 1));
	str[str_size] = 0;
	memset(str, 48, str_size);
	printf("The next line should contain %zu '%c' and %zu '%c'\n", str_size, filler, (size_t)0 , memset_value);
	printf("%s\n", str);
	ft_memset(str + memset_start, memset_value, memset_size);
	printf("The next line should start with %zu '%c' followed by %zu '%c'\n", (memset_size) ? memset_start : str_size, filler, memset_size, memset_value);
	printf("%s\n", str);
	if (memset_start + memset_size != str_size)
		if (str[memset_start + memset_size] != filler)
			*error = TRUE;
	for (size_t t = 0; t != memset_start; t++)
		if (str[t] != filler)
			*error = TRUE;
	for (size_t r = memset_start; r != memset_start + memset_size; r++)
		if (str[r] != memset_value)
			*error = TRUE;
	return (__func__);
}

int	main(void)
{
	size_t nb_func = 6, index = 0;
	const char *error_list[nb_func + 1];
	short int error = FALSE, nb_error = 0;
	const char *(*f[nb_func])(short int*);
	const char	*func_ret;
	bzero(f, nb_func);
	bzero(error_list, nb_func + 1);
	f[0] = &casual_memset;
	f[1] = &border_memset;
	f[2] = &big_memset;
	f[3] = &empty_memset;
	f[4] = &little_memset;
	f[5] = &return_memset;
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
