/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:40 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:15:11 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int			ft_strmatch(char *s1, char *s2)
{
	int			i;
	int			j;
	int			ret;

	i = 0;
	j = 0;
	ret = ft_strlen(s2);
	while (s1[i])
	{
		j = 0;
		while (s1[i] != s2[j] && s1[i] && s2[j])
			j++;
		i++;
		if (j <= ret)
			ret = j;
	}
	if (ret == (int)ft_strlen(s2))
		return (-1);
	return (ret);
}
