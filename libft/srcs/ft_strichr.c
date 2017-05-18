/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strichr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 10:31:02 by ade-sede          #+#    #+#             */
/*   Updated: 2016/12/05 16:03:25 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t		ft_strichr(char *s, char c)
{
	ssize_t	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] != c && s[i])
		i++;
	if (s[i] == c)
		return (i);
	return (-1);
}
