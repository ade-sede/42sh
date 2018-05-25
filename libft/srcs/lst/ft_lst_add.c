/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:39 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:56 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	ft_simple_lst_add(t_list **first, t_list *new_node)
{
	if (new_node)
	{
		if (*first != NULL)
			new_node->next = *first;
		*first = new_node;
	}
}

void	ft_genlst_add(void *first, void *new)
{
	t_gen_lst **first_cast;
	t_gen_lst *new_cast;

	new_cast = new;
	first_cast = first;
	if (new)
	{
		if (*first_cast != NULL)
			new_cast->next = *first_cast;
		*first_cast = new_cast;
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
		if (!(*head)->last)
			(*head)->last = new_node;
		if (!(*head)->middle)
			(*head)->middle = new_node;
	}
	ft_lst_replace_middle(head);
}
