/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:54 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:07:01 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "str.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;

	little_len = ft_strlen(little);
	if (!*little)
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
