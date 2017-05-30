/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 15:24:03 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/26 14:28:38 by ade-sede         ###   ########.fr       */
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

static const char	*return_memcpy(short *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	char	src[] = "test basic du memcpy !";
	char	buff1[22];

	char	*r1 = memcpy(buff1, src, 22);
	char	*r2 = ft_memcpy(buff1, src, 22);
	if (r1 != r2)
		*error = TRUE;

	r1 = memcpy("", src, 0);
	r2 = ft_memcpy("", src, 0);
	if (r1 != r2)
		*error = TRUE;
	return (__func__);
}

static const char	*big_addr_memcpy(short *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	void	**src;
	size_t	src_size = 490;
	void	**dst;
	size_t	dst_size = src_size;

	src = malloc(sizeof(*src) * src_size);
	bzero(src, sizeof(*src) * src_size);
	dst = malloc(sizeof(*dst) * dst_size);
	bzero(dst, sizeof(*dst) * dst_size);
	for (int i = 0; i < src_size ; i++)
		src[i] = malloc(8);
	ft_memcpy(dst, src, src_size * sizeof(*src));
	for (int i = 0; i < src_size ; i++)
	{
		if (dst[i] != src[i])
			*error = TRUE;
		/* printf("%d -> %p\n", dst[i]); */
		/* printf("%d -> %p\n", src[i]); */
	}

	return (__func__);
}

static const char	*casual_addr_memcpy(short *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	void	**src;
	size_t	src_size = 10;
	void	**dst;
	size_t	dst_size = src_size;

	src = malloc(sizeof(*src) * src_size);
	bzero(src, sizeof(*src) * src_size);
	dst = malloc(sizeof(*dst) * dst_size);
	bzero(dst, sizeof(*dst) * dst_size);
	for (int i = 0; i < src_size ; i++)
		src[i] = malloc(8);
	ft_memcpy(dst, src, src_size * sizeof(*src));
	for (int i = 0; i < src_size ; i++)
	{
		if (dst[i] != src[i])
			*error = TRUE;
		printf("%d -> %p\n", dst[i]);
		printf("%d -> %p\n", src[i]);
	}

	return (__func__);
}

static const char	*big_str_memcpy(short *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	void	*src = "This is a very veyr very big qwe qwe wqe qe qw eqw eqwe qwe qwe qwe oqe oiqw oijetest string";
	size_t	src_size = strlen(src);
	size_t	memcpy_dst_start = 1;
	size_t	memcpy_src_start = 0;
	size_t	memcpy_size = src_size + 1;
	size_t	memcpy_dst_end = memcpy_dst_start + memcpy_size;
	size_t	memcpy_src_end = memcpy_src_start + memcpy_size;
	size_t	dst_size = memcpy_size + 1;
	void	*dst = malloc(dst_size);

	/* bzero(dst, dst_size); */
	ft_memcpy(dst + memcpy_dst_start, src + memcpy_src_start, memcpy_size);
	((char*)dst)[0] = '0';
	printf("Source = %s\n", src);
	printf("Dest = %s\n", dst);
	if (src_size > (memcpy_src_end))
		((unsigned char*)src)[memcpy_src_end] = 0;
	if (strcmp(src + memcpy_src_start, dst + memcpy_dst_start) != 0)
		*error = TRUE;
	return (__func__);
}

static const char	*casual_str_memcpy(short *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	void	*src = "a";
	size_t	src_size = strlen(src);
	size_t	memcpy_dst_start = 0;
	size_t	memcpy_src_start = 0;
	size_t	memcpy_size = src_size + 1;
	size_t	memcpy_dst_end = memcpy_dst_start + memcpy_size;
	size_t	memcpy_src_end = memcpy_src_start + memcpy_size;
	size_t	dst_size = memcpy_size;
	void	*dst = malloc(dst_size);
	bzero(dst, src_size + 1);
	ft_memcpy(dst + memcpy_dst_start, src + memcpy_src_start, memcpy_size);
	printf("Source = %s\n", src);
	printf("Dest = %s\n", dst);
	if (src_size > (memcpy_src_end))
		((unsigned char*)src)[memcpy_src_end] = 0;
	if (strcmp(src + memcpy_src_start, dst + memcpy_src_start) != 0)
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
	f[0] = &casual_str_memcpy;
	f[1] = &big_str_memcpy;
	f[2] = &casual_addr_memcpy;
	f[3] = &big_addr_memcpy;
	f[4] = &return_memcpy;
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
