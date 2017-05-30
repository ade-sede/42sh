/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 18:38:07 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/28 17:27:04 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "str.h"
#include "mem.h"

static void	align_memory(unsigned char **s, unsigned char c, size_t *n)
{
	while (n && **s != c && (((t_ulong)*s & (ULONG_SIZE -1)) != 0))
	{
		(*s)++;
		(*n)--;
	}
}

static void	*cmp_last_bits(const void *s, int c, size_t *n)
{
	while (n)
	{
		if (*(unsigned char*)s == (unsigned char)c)
			return ((void*)s);
		(*n)--;
		s++;
	}
	return (NULL);
}

static void	*chr_longword(const void **s, int c, size_t *n)
{
	size_t	xlen;
	t_ulong	*s_ptr;

	xlen = (*n / ULONG_SIZE);
	(*n) %= ULONG_SIZE;
	s_ptr = (t_ulong*)*s;
	while (xlen)
	{
		if ((HAS_VALUE(*s_ptr, CHAR_TO_LONG((unsigned char)c))))
			return (cmp_last_bits((const void*)s_ptr, c, n));
		xlen--;
		s_ptr++;
	}
	*s = s_ptr;
	return (NULL);
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	void	*ptr;

	ptr = NULL;
	align_memory((unsigned char**)&s, (unsigned char)c, &n);
	if (*(unsigned char*)s == (unsigned char)c)
		return ((void*)s);
	if (n >= ULONG_SIZE)
		if ((ptr = chr_longword(&s, c, &n)) != NULL)
			return (ptr);
	if (n)
		cmp_last_bits(s, c, &n);
	return (NULL);
}
