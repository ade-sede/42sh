/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_foreach.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:39 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:57 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	ft_double_lst_foreach(t_list_d *start, t_list_d *end, \
		void (*f)(t_list_d*), int order)
{
	if (start)
	{
		if (order == 1)
		{
			while (start != end)
			{
				(*f)(start);
				start = start->next;
			}
		}
		else if (order == -1)
		{
			while (start != end)
			{
				(*f)(start);
				start = start->prev;
			}
		}
	}
}

void	ft_simple_lst_foreach(t_list *start, t_list *end, void (*f)(t_list*))
{
	if (start)
	{
		while (start != end)
		{
			(*f)(start);
			start = start->next;
		}
	}
}
