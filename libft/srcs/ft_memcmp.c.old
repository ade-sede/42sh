/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 17:35:32 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/28 17:35:32 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mem.h"

static int	align_memory(unsigned char **s1, unsigned char **s2, size_t *n)
{
	while (*n && (((t_ulong)*s1 & (ULONG_SIZE -1)) != 0))
	{
		if (**s1 != **s2)
			return (**s1 - **s2);
		(*s1)++;
		(*s2)++;
		(*n)--;
	}
	return ((unsigned char)**s1 - (unsigned char)**s2);
}

static int	cmp_last_bits(unsigned char *s1, unsigned char *s2, size_t *n)
{
	while (n)
	{
		if ((unsigned char)*s1 != (unsigned char)*s2)
			return (*s1 - *s2);
		s1++;
		s2++;
		(*n)--;
	}
	return (0);
}

static int cmp_longword(const void **s1, const void **s2, size_t *n)
{
	size_t	xlen;
	t_ulong	*s1_ptr;
	t_ulong	*s2_ptr;

	xlen = (*n / ULONG_SIZE);
	(*n) %= ULONG_SIZE;
	s1_ptr = (t_ulong*)*s1;
	s2_ptr = (t_ulong*)*s2;
	while (xlen)
	{
		if (s1_ptr != s2_ptr)
			return(cmp_last_bits((unsigned char*)s1_ptr, (unsigned char*)s2_ptr, n));
		s1_ptr++;
		s2_ptr++;
		xlen--;
	}
	*s1 = s1_ptr;
	*s2 = s2_ptr;
	return (0);
}

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int	ret;

	if ((ret = align_memory((unsigned char**)&s1, (unsigned char**)&s2, &n)) != 0)
		return (ret);
	if (n >= ULONG_SIZE)
		ret = cmp_longword(&s1, &s2, &n);
	if (n)
		ret = cmp_last_bits((unsigned char*)s1, (unsigned char*)s2, &n);
	return (ret);
}
