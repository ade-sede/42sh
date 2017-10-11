/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:41:24 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/11 22:41:41 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mem.h"

void				*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*d;
	unsigned char	*s;
	unsigned char	target;

	d = (unsigned char*)dst;
	s = (unsigned char*)src;
	target = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if ((*d++ = *s++) == target)
			return (d);
		i++;
	}
	return (NULL);
}
