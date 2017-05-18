/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 15:20:23 by ade-sede          #+#    #+#             */
/*   Updated: 2016/11/13 22:49:05 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
