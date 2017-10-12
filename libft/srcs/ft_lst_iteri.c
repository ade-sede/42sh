/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_iteri.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:41:24 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/11 22:41:41 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "list.h"

void	ft_simple_lst_iteri(t_list *start, t_list *end, \
		void (*f)(t_list*, size_t))
{
	size_t	i;

	i = 0;
	if (start)
	{
		while (start != end)
		{
			(*f)(start, i);
			i++;
			start = start->next;
		}
	}
}

void	ft_double_lst_iteri(t_list_d *start, t_list_d *end, \
		void (*f)(t_list_d*, size_t), int order)
{
	size_t	i;

	i = 0;
	if (start)
	{
		if (order == 1)
		{
			while (start != end)
			{
				(*f)(start, i);
				i++;
				start = start->next;
			}
		}
		else if (order == -1)
		{
			while (start != end)
			{
				(*f)(start, i);
				i++;
				start = start->prev;
			}
		}
	}
}
