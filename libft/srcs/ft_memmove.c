/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:41:24 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/11 22:41:41 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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
