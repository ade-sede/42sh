/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simple_lst_del_one.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:39 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:59 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	ft_simple_lst_del_one(t_list **first, t_list *node, void (*f)(void*))
{
	t_list	*old_tmp;
	t_list	*curr_tmp;

	if (node)
	{
		curr_tmp = *first;
		old_tmp = curr_tmp;
		while (curr_tmp && curr_tmp != node)
		{
			old_tmp = curr_tmp;
			curr_tmp = curr_tmp->next;
		}
		if (*first == node)
			*first = node->next;
		else
			old_tmp->next = curr_tmp->next;
		if (f)
			(f)(node->data);
		free(node);
	}
}

void	ft_genlst_del_one(void *first, void *node, void (*f)(void*))
{
	t_gen_lst	**first_cast;
	t_gen_lst	*node_cast;
	t_gen_lst	*old_tmp;
	t_gen_lst	*curr_tmp;

	first_cast = first;
	node_cast = node;
	if (node_cast)
	{
		curr_tmp = *first_cast;
		old_tmp = curr_tmp;
		while (curr_tmp && curr_tmp != node_cast)
		{
			old_tmp = curr_tmp;
			curr_tmp = curr_tmp->next;
		}
		if (*first_cast == node_cast)
			*first_cast = node_cast->next;
		else
			old_tmp->next = curr_tmp->next;
		if (f)
			(f)(node_cast);
		free(node_cast);
	}
}
