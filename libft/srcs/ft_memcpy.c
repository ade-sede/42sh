/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 14:54:11 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/20 19:34:18 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*s1;

	s1 = dst;
	while (n != 0)
	{
		*s1 = *(unsigned char*)src;
		s1++;
		src++;
		n--;
	}
	return (dst);
}


void	**ft_addrcpy(void **dst, const void **src, size_t n)
{
	void	**s1;

	s1 = dst;
	while (n != 0)
	{
		*s1 = *(void**)src;
		s1++;
		src++;
		n--;
	}
	return (dst);
}
