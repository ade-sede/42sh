/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 18:30:14 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 20:59:21 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "bang.h"
#include "history.h"

int	read_hist_numeric(int count, t_word *event, t_hist *hist)
{
	t_list_d	*start_point;
	t_list_d	*event_node;

	if (!hist->list || !hist->list->first || !hist->list->last)
		return (TRUE);
	if (count == 0)
		return (FALSE);
	if (count < 0)
		start_point = hist->list->first;
	else
		start_point = hist->list->last;
	count *= -1;
	event_node = ft_double_lst_get_n(start_point, count);
	if (!event_node)
		return (TRUE);
	w_addstr(event, event_node->data);
	return (FALSE);
}

int	read_hist_string(int flag, t_word string_event, t_word *event, t_hist *hist)
{
	t_list_d	*node;

	if (!hist->list || !hist->list->first)
		return (TRUE);
	node = hist->list->first;
	if (!string_event.str)
		return (TRUE);
	if (flag == 1)
	{
		while (node && !ft_strstr(node->data, string_event.str))
			node = node->next;
	}
	else
	{
		while (node && \
				!ft_strnequ(string_event.str, node->data, string_event.actlen))
			node = node->next;
	}
	if (!node)
		return (TRUE);
	w_addstr(event, node->data);
	return (FALSE);
}
