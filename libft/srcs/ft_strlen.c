/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 12:13:14 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 12:14:36 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "str.h"
#include <string.h>

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (*s != '\0')
	{
		i++;
		s++;
	}
	return (i);
}

size_t	ft_strlen_color(char *str)
{
	size_t	i;

	i = 0;
	while (*str)
	{
		if (*str == '\e')
		{
			while (*str && *str != 'm')
				str++;
			str++;
			if (!*str)
				return (i);
		}
		str++;
		i++;
	}
	return (i);
}
