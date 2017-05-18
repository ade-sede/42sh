/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 17:36:09 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/12 11:08:29 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"

void	ft_simple_lst_add(t_list **first, t_list *new_node)
{
	if (new_node)
	{
		new_node->next = *first;
		*first = new_node;
	}
	else
		ft_dprintf(2, "Param new_node in fcts %s is null\n", __func__);
}

void	ft_double_lst_add(t_lst_head **head, t_list_d *new_node)
{
	if (new_node)
	{
		new_node->next = (*head)->first;
		(*head)->first->prev = new_node;
		(*head)->first = new_node;
		(*head)->shift_middle -= 1;
		(*head)->node_count += 1;
	}
	else
		ft_dprintf(2, "Param new_node in fcts %s is null\n", __func__);
	ft_lst_replace_middle(head);
}
