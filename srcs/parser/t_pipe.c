/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 15:13:49 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/17 15:15:53 by ade-sede         ###   ########.fr       */
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
