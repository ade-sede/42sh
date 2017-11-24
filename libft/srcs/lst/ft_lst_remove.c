/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_remove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:39 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:58 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	ft_simple_lst_remove(t_list **first, void (*f)(void*))
{
	t_list	*node;
	t_list	*tmp_next;

	node = *first;
	while (node)
	{
		tmp_next = node->next;
		ft_simple_lst_del_one(first, node, (f));
		node = tmp_next;
	}
	*first = NULL;
}

void	ft_genlst_remove(void *first, void (*f)(void*))
{
	t_gen_lst		**first_cast;
	t_gen_lst		*node;
	t_gen_lst		*tmp_next;

	first_cast = first;
	node = *first_cast;
	while (node)
	{
		tmp_next = node->next;
		ft_genlst_del_one(first_cast, node, (f));
		node = tmp_next;
	}
	*first_cast = NULL;
}

void	ft_double_lst_remove(t_lst_head **head, void (*f)(void*))
{
	t_list_d	*curr;
	t_list_d	*next;

	if (!head || !*head)
		return ;
	curr = ((*head)->first);
	while (curr)
	{
		next = curr->next;
		if (curr->data && f)
			(f)(curr->data);
		free(curr);
		curr = next;
	}
	(*head)->first = NULL;
	(*head)->middle = NULL;
	(*head)->last = NULL;
}

void	ft_remove_head(t_lst_head **head, void (*f)(void*))
{
	if (!*head)
		return ;
	ft_double_lst_remove(head, (f));
	free(*head);
	*head = NULL;
}
