/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 15:33:05 by ade-sede          #+#    #+#             */
/*   Updated: 2017/02/01 14:25:08 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *s1, size_t n)
{
	size_t	i;
	char	*dest;

	i = 0;
	if ((dest = ft_strnew(n + 1)) == NULL)
		return (NULL);
	while (s1[i] && i != n)
	{
		dest[i] = s1[i];
		i++;
	}
	return (dest);
}
