/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:39 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:15:01 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"
#include "str.h"
#include "color.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	if (count * size == 0)
	{
		ft_putendl("Calloc exit");
		exit(1);
	}
	mem = malloc(count * size);
	if (!mem)
	{
		ft_putendl("Calloc exit");
		exit(1);
	}
	ft_bzero(mem, size);
	return (mem);
}
