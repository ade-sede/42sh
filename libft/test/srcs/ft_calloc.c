/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 19:57:44 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/29 12:13:03 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"
#include "mem.h"
#include "str.h"
#include "color.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	if (count * size == 0)
	{
		ft_putendl(RED"Calloc exit"RESET);
		exit(1);
	}
	mem = malloc(count * size);
	if (!mem)
	{
		ft_putendl(RED"Calloc exit"RESET);
		exit(1);
	}
	ft_bzero(mem, size);
	return (mem);
}
