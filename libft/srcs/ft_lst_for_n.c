/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_for_n.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 02:10:19 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/16 02:10:24 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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
