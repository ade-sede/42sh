/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:41:24 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/19 12:45:18 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "list.h"

/*
**	Creates a copy of the original list. Each node is a new one, with a fresh
**	address, but the original list and the copy both have the same data.
**	It must never be freed in both list.
*/

void	ft_simple_lst_dup(t_list **new_list_first, t_list *original)
{
	t_list	*new_node;

	new_node = NULL;
	if (!new_list_first)
		return ;
	while (original)
	{
		new_node = ft_simple_lst_create(original->data);
		ft_simple_lst_pushback(new_list_first, new_node);
		original = original->next;
	}
}
