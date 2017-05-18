/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 20:44:40 by ade-sede          #+#    #+#             */
/*   Updated: 2017/02/10 15:21:24 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

intmax_t	ft_atoi_base(char *str, int base)
{
	int			i;
	intmax_t	res;
	int			neg;

	neg = 0;
	res = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = 1;
		i++;
	}
	while (ft_ishex(str[i]))
	{
		if (str[i] - 'A' >= 0)
			res = res * base + (str[i] - 55);
		else
			res = res * base + (str[i] - 48);
		i++;
	}
	return ((neg == 1) ? -(res) : res);
}
