/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_iteri.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 16:23:16 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/21 17:00:55 by ade-sede         ###   ########.fr       */
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
