/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrcmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:54 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:07:02 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "str.h"
#include <stdio.h>

/*
**	Can we find the string little at the end of big ?
*/

int	ft_strrcmp(const char *big, const char *little)
{
	int		big_index;
	int		little_index;

	big_index = ft_strlen(big) - 1;
	little_index = ft_strlen(little) - 1;
	if (little_index > big_index)
		return (-1);
	while (big_index && little_index && big[big_index] == little[little_index])
	{
		big_index--;
		little_index--;
	}
	if (little_index == 0 && big[big_index] == little[little_index])
		return (0);
	return (big[big_index] - little[little_index]);
}
