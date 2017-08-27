/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 12:13:14 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 12:14:46 by vcombey          ###   ########.fr       */
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
