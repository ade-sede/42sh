/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_for_n.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:39 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:57 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	ft_double_lst_for_n(t_list_d *start, int count, void (*f)(t_list_d*), \
		int order)
{
	while (start && count)
	{
		(*f)(start);
		if (order == 1)
			start = start->next;
		if (order == -1)
			start = start->prev;
		count--;
	}
}

void	ft_simple_lst_for_n(t_list *start, int count, void (*f)(t_list*))
{
	while (start && count)
	{
		(*f)(start);
		start = start->next;
		count--;
	}
}
