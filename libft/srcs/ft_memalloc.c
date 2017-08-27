/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 12:13:14 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 12:13:57 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "alloc.h"
#include "str.h"
#include "mem.h"
#include "color.h"

/*
**	Allocates a memory and puts it to zero.
**	This function is meant to allocate memory for strings
*/

void	*ft_memalloc(size_t size)
{
	void	*mem;

	if (size)
		mem = malloc(size);
	else
		mem = NULL;
	if (!mem)
	{
		ft_putendl(RED"Memalloc exit\n"RESET);
		exit(1);
	}
	ft_bzero(mem, size);
	return (mem);
}
