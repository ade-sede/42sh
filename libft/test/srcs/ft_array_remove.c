/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_remove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 16:27:32 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/29 16:36:59 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"
#include "mem.h"
#include "libft.h"

void	*ft_array_remove_index(size_t index, t_ulong coef, size_t curr_size, void *ptr)
{
	void	*new_memory;
	size_t	size;

	size = curr_size - (1 * coef);
	if (!ptr)
		return (palloc(size));
	else if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	else
	{
		new_memory = palloc(size);
		ft_memcpy(new_memory, ptr, index * coef);
		ft_memcpy(new_memory + (index * coef), ptr + index * coef + 1, size - index * coef); 
	}
}
