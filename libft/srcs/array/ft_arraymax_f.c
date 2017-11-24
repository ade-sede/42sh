/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraymax_f.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:38 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:48 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

static size_t	ft_max_size_t(size_t a, size_t b)
{
	return ((a > b) ? a : b);
}

size_t			ft_arraymax_f(char **str, size_t (*f)(char *))
{
	size_t	max;

	max = 0;
	while (str && *str)
	{
		max = ft_max_size_t(f(*str), max);
		str++;
	}
	return (max);
}
