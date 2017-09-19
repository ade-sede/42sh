/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:54 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:07:04 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "alloc.h"
#include "mem.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*little_str;

	if ((!s) || len == 0)
		return (NULL);
	little_str = palloc(sizeof(char) * (len + 1));
	ft_memcpy(little_str, s + start, len);
	little_str[len] = '\0';
	return (little_str);
}

char	*cl_strsub(char const *s, unsigned int start, size_t len)
{
	char	*little_str;

	if ((!s) || len == 0)
		return (NULL);
	little_str = ft_memalloc(sizeof(char) * (len + 1));
	ft_memcpy(little_str, s + start, len);
	return (little_str);
}
