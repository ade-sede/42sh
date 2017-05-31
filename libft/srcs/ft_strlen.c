/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */ /*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */ /*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 18:33:28 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/25 19:38:34 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "libft.h"

/*
**	1) Align memory
**	2) Check if one of the Bytes in your 8 Bytes is set to 0
**	3) Find wich one it is
*/

static int		align_memory(const char **align_ptr)
{
	while (((t_ulong)*align_ptr & (ULONG_SIZE - 1)) != 0)
	{
		if (**align_ptr == 0)
			return (1);
		(*align_ptr)++;
	}
	return (0);
}

static ssize_t	find_bit(const char *cp)
{
	if (cp[0] == 0)
		return (0);
	if (cp[1] == 0)
		return (1);
	if (cp[2] == 0)
		return (2);
	if (cp[3] == 0)
		return (3);
	if (cp[4] == 0)
		return (4);
	if (cp[5] == 0)
		return (5);
	if (cp[6] == 0)
		return (6);
	if (cp[7] == 0)
		return (7);
	return (-1);
}

size_t			ft_strlen(const char *origin)
{
	const char	*align_ptr;
	t_ulong		*longword_ptr;
	t_ulong		longword;
	ssize_t		diff;
	const char	*cp;

	align_ptr = origin;
	if (align_memory(&align_ptr))
		return (align_ptr - origin);
	longword_ptr = (t_ulong*)align_ptr;
	while (42)
	{
		longword = *longword_ptr++;
		if (HAS_ZERO(longword))
		{
			cp = (const char*)(longword_ptr - 1);
			diff = find_bit(cp);
			if (diff != -1)
				return (cp + diff - origin);
		}
	}
	return (0);
}
