/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraymax_f.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 16:23:16 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/21 16:33:41 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "array.h"

static size_t	ft_max_size_t(size_t a, size_t b)
{
	return ((a > b) ? a : b);
}

size_t			ft_arraymax_f(const char **str, size_t (*f)(const char *))
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
