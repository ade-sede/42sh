/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:50 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:30 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "libft.h"

t_pipe	*create_pipe(int *p)
{
	t_pipe	*new;

	if (!p)
		return (NULL);
	new = ft_memalloc(sizeof(*new));
	new->p = p;
	return (new);
}

void	free_pipe(void *pipe)
{
	t_pipe *a;

	a = (t_pipe*)pipe;
	if (a)
	{
		free(a->p);
		free(a);
	}
}