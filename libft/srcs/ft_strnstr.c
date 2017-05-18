/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 15:01:24 by ade-sede          #+#    #+#             */
/*   Updated: 2016/11/14 13:23:33 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;

	little_len = ft_strlen(little);
	if (little[0] == '\0')
		return ((char*)big);
	while (*big && len)
	{
		if (ft_strncmp(big, little, little_len) == 0 && little_len <= len)
			return ((char*)big);
		big++;
		len--;
	}
	return (NULL);
}
