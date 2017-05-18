/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 15:55:45 by ade-sede          #+#    #+#             */
/*   Updated: 2016/11/12 15:44:16 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
