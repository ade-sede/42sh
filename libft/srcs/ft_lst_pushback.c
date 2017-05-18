/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_pushback.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 18:23:07 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/12 11:09:04 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"

void	ft_simple_lst_pushback(t_list **first, t_list *new_node)
{
	t_list	*tmp;
	t_list	*old_tmp;

	if (!new_node)
		ft_dprintf(2, "Param new_node in fcts %s is null\n", __func__);
	else
	{
		tmp = *first;
		while (tmp)
		{
			old_tmp = tmp;
			tmp = tmp->next;
		}
		old_tmp->next = new_node;
	}
}

void	ft_double_lst_pushback(t_lst_head **head, t_list_d *new_node)
{
	t_list_d	*prev;

	if (new_node)
	{
		prev = (*head)->last;
		new_node->prev = prev;
		prev->next = new_node;
		(*head)->last = new_node;
		(*head)->shift_middle += 1;
		(*head)->node_count += 1;
	}
	else
		ft_dprintf(2, "Param new_node in fcts %s is null\n", __func__);
	ft_lst_replace_middle(head);
}
