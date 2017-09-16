/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_rev.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 02:10:19 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/16 02:10:54 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_simple_lst_rev(t_list **lst)
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
