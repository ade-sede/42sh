/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:40:47 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/11 22:40:58 by vcombey          ###   ########.fr       */
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
