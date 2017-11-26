/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_backslash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:39 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:15:06 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

int		ft_is_backslash(char *str, int n)
{
	int	i;
	int	res;

	res = 0;
	i = n;
	if (i == 0)
		return (0);
	i--;
	while (i >= 0 && str[i] == '\\')
	{
		res = res == 0 ? 1 : 0;
		i--;
	}
	return (res);
}
