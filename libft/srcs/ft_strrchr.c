/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 02:10:19 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/16 02:10:24 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*found;
	const char	*tmp;

	if (c == 0)
		return (ft_strchr(s, 0));
	found = NULL;
	while ((tmp = ft_strchr(s, c)))
	{
		found = tmp;
		s = tmp + 1;
	}
	return ((char*)found);
}

ssize_t	ft_strrichr(const char *s, int c)
{
	char	*ptr;

	ptr = ft_strrchr(s, c);
	return ((ptr) ? ptr - s : -1);
}
