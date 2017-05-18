/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_remove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 17:39:03 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/11 16:32:37 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


void	ft_simple_lst_remove(t_list	**first, void (*f)(void*))
{
	t_list	*node;

	node = *first;
	while (node)
	{
		ft_simple_lst_del_one(first, node, (f));
		node = node->next;
	}
	*first = NULL;
}

void	ft_double_lst_remove(t_lst_head **head, void (*f)(void*))
{
	t_list_d	*curr;
	t_list_d	*next;

	curr = ((*head)->first);
	while (curr)
	{
		next = curr->next;
		ft_double_lst_del_one(head, curr, (f));
		curr = next;
	}
	(*head)->first = NULL;
	(*head)->middle = NULL;
	(*head)->last = NULL;
}

void	ft_remove_head(t_lst_head **head, void (*f)(void*))
{
	ft_double_lst_remove(head, (f));
	free(*head);
	*head = NULL;
}
