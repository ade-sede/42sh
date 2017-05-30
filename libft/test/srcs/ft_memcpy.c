/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 17:54:37 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/28 17:20:52 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"
#include "libft.h"
#include <string.h>
#include <stdio.h>

/*
**	Copies n bytes from src to dest.
**	Copying 8 Bytes a time if the size allows it
*/

static void	align_memory(unsigned char **dst, unsigned char **src, size_t *n)
{
	while (n && (((t_ulong)*dst & (ULONG_SIZE - 1)) != 0))
	{
		n--;
		**dst = **src;
		(*dst)++;
		(*src)++;
	}
}

static void	copy_longword(void **dst, const void **src, size_t *n)
{
	size_t	xlen;
	t_ulong	*dst_ptr;
	t_ulong	*src_ptr;

	xlen = (*n / ULONG_SIZE);
	dst_ptr = (t_ulong*)*dst;
	src_ptr = (t_ulong*)*src;
	while (xlen)
	{
		*dst_ptr = *src_ptr;
		dst_ptr++;
		src_ptr++;
		xlen--;
	}
	*n %= ULONG_SIZE;
	*dst = dst_ptr;
	*src = src_ptr;
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*original;

	original = dst;
	align_memory((unsigned char**)&dst, (unsigned char**)&src, &n);
	if (n >= ULONG_SIZE)
		copy_longword(&dst, &src, &n);
	while (n)
	{
		n--;
		*(unsigned char*)dst = *(unsigned char*)src;
		dst++;
		src++;
	}
	return (original);
}
