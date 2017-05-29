/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 17:53:39 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/26 18:25:57 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "str.h"

static int	align_memory(const char **s1, const char **s2)
{
	while (**s1 && **s2 && (((t_ulong)*s1 & (ULONG_SIZE -1)) != 0))
	{
		if ((unsigned char)**s1 != (unsigned char)**s2)
			return ((unsigned char)**s1 - (unsigned char)**s2);
		(*s1)++;
		(*s2)++;
	}
	return ((unsigned char)**s1 - (unsigned char)**s2);
}

static int	cmp_last_bits(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if ((unsigned char)*s1 != (unsigned char)*s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	int	ret;
	t_ulong	*s1_ptr;
	t_ulong	*s2_ptr;

	if ((ret = align_memory(&s1, &s2)) != 0)
		return (ret);
	s1_ptr = (t_ulong*)s1;
	s2_ptr = (t_ulong*)s2;
	while (42)
	{
		if ((HAS_ZERO(*s1_ptr)) || (HAS_ZERO(*s2_ptr)) || s1_ptr != s2_ptr)
			return(cmp_last_bits((const char*)s1_ptr, (const char*)s2_ptr));
		s1_ptr++;
		s2_ptr++;
	}
	return (0);
}
