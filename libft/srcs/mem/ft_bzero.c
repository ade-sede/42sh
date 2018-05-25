/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:39 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:15:01 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

/*
**	Align memory
*/

static void	align_memory(unsigned char **ptr, size_t *n)
{
	while (*n && (((t_ulong)*ptr & (ULONG_SIZE - 1)) != 0))
	{
		(*n)--;
		**ptr = 0;
		(*ptr)++;
	}
}

/*
**	Set len bytes from ptr to 0
*/

void		ft_bzero(void *ptr, size_t len)
{
	size_t	xlen;
	t_ulong	*ul_ptr;

	align_memory((unsigned char**)&ptr, &len);
	ul_ptr = (t_ulong*)ptr;
	if (len >= ULONG_SIZE)
	{
		ul_ptr = (t_ulong*)ptr;
		xlen = (len / ULONG_SIZE) + 1;
		while (--xlen)
		{
			*ul_ptr = 0;
			ul_ptr++;
		}
	}
	len %= ULONG_SIZE;
	if (len > 0)
	{
		ptr = ul_ptr;
		while (len--)
		{
			*(unsigned char*)ptr = 0;
			ptr++;
		}
	}
}
