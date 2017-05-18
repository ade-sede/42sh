/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 18:29:46 by ade-sede          #+#    #+#             */
/*   Updated: 2016/11/10 18:35:11 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*memory;

	if ((memory = (void*)malloc(sizeof(unsigned char) * size)) == NULL)
		return (NULL);
	ft_bzero(memory, size);
	return (memory);
}
