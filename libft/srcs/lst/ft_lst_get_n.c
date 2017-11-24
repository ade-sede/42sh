/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_get_n.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:39 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:57 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

/*
** Get the n'th node of the list from where we are. first is node 1
** first->next is node 2
*/

t_list_d	*ft_double_lst_get_n(t_list_d *first, int n)
{
	if (n == 0)
		return (NULL);
	if (!first)
		return (NULL);
	if (n > 0)
	{
		while (first && n > 1)
		{
			n--;
			if (first->next)
				first = first->next;
		}
	}
	else if (n < 0)
	{
		while (first && n < -1)
		{
			n++;
			if (first->prev)
				first = first->prev;
		}
	}
	return (first);
}

t_list_d	*ft_double_lst_get_n_fail(t_list_d *first, int n)
{
	if (n == 0)
		return (NULL);
	if (!first)
		return (NULL);
	if (n > 0)
	{
		while (first && n > 1)
		{
			n--;
			if (first->next)
				first = first->next;
		}
	}
	else if (n < 0)
	{
		while (first && n < -1)
		{
			n++;
			if (first->prev)
				first = first->prev;
		}
	}
	if (n != 1 && n != -1)
		return (NULL);
	return (first);
}

/*
**	0 is the current node, 1 is node->next;
*/

t_list		*ft_simple_lst_get_n(t_list *first, size_t n)
{
	if (n == 0)
		return (first);
	while (first && n)
	{
		n--;
		first = first->next;
	}
	return (first);
}

void		*ft_genlst_get_n(void *first, int n)
{
	t_gen_lst	*first_cast;

	first_cast = first;
	if (n < 0)
		n = ft_genlst_len(first) - n;
	if (n < 0)
		return (NULL);
	while (first_cast && n)
	{
		n--;
		first_cast = first_cast->next;
	}
	return (first_cast);
}
