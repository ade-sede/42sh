/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraymax_f.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:51 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:37 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "array.h"

static size_t	ft_max_size_t(size_t a, size_t b)
{
	return ((a > b) ? a : b);
}

size_t			ft_arraymax_f(char **str, size_t (*f)(char *))
{
	size_t	max;

	max = 0;
	while (*str)
	{
		max = ft_max_size_t(f(*str), max);
		str++;
	}
	return (max);
}
