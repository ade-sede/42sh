/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_rev.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 14:42:56 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/12 14:49:48 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void   ft_simple_lst_rev(t_list **lst)
{
	t_list *a;
	t_list *b;
	t_list *c;

	a = NULL;
	b = *lst;
	c = b->next;
	while (b)
	{
		b->next = a;
		a = b;
		b = c;
		if (c)
			c = c->next;
	}
	*lst = a;
}
