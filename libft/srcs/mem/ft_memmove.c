/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:39 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:15:03 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst >= src && dst <= src + len)
	{
		while (len--)
			*(unsigned char*)(dst + len) = *(unsigned char*)(src + len);
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
