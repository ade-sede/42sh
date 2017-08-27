/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 12:13:14 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 12:13:41 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "list.h"

void	ft_simple_lst_add(t_list **first, t_list *new_node)
{
	if (new_node)
	{
		if (first == NULL || *first == NULL)
			*first = new_node;
		else
		{
			new_node->next = *first;
			*first = new_node;
		}
	}
}

void	ft_double_lst_add(t_lst_head **head, t_list_d *new_node)
{
	if (new_node)
	{
		if ((*head)->first)
		{
			new_node->next = (*head)->first;
			(*head)->first->prev = new_node;
			(*head)->first = new_node;
			(*head)->shift_middle -= 1;
			(*head)->node_count += 1;
		}
		else
		{
			(*head)->node_count += 1;
			(*head)->first = new_node;
			(*head)->middle = new_node;
		}
	}
	ft_lst_replace_middle(head);
}
