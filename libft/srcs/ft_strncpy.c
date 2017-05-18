/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 18:13:15 by ade-sede          #+#    #+#             */
/*   Updated: 2016/11/12 19:32:01 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i != len && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (ft_strlen(src) < len)
		while (i != len)
		{
			dst[i] = '\0';
			i++;
		}
	return (dst);
}
