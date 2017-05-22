/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 13:07:03 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/22 19:43:41 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != c && *s)
		s++;
	if (*s == c)
		return ((char*)s);
	return (NULL);
}

const char	**ft_arraychr(const char **array, const char *str)
{
	if (!array || !str)
		return (NULL);
	while (*array && !ft_strequ(*array, str))
		array++;
	if (*array)
		return (array);
	return (NULL);
}
