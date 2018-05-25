/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_safe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:39 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:15:05 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

static int	set_result_int(int *result)
{
	*result = -2147483648;
	return (1);
}

int			ft_atoi_safe(const char *str, int *result)
{
	int	sign;

	*result = 0;
	sign = 0;
	while (*str == ' ' || ('\t' <= *str && *str <= '\r'))
		str++;
	if (ft_strcmp(str, "-2147483648") == 0)
		return (set_result_int(result));
	if (*str == '+' || *str == '-')
	{
		sign = (*str == '-' ? -1 : 1);
		str++;
	}
	if (*str == '\0')
		return (0);
	while ('0' <= *str && *str <= '9')
	{
		*result = (*result * 10) + (*str - '0');
		str++;
	}
	*result = sign == -1 ? -(*result) : *result;
	if (*str != '\0')
		return (0);
	return (1);
}
