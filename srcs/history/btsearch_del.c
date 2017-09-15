/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btsearch_del.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 22:41:03 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/15 22:41:13 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"
#include "history.h"
#include <stdio.h>

void	btsearch_del(t_line *line, t_hist *h)
{
	if (!btsearch_prev(line, h))
	{
		if (h->btsearch_list)
			ft_remove_head(&h->btsearch_list, NULL);
		if (h->btsearch_buff_len > 0)
		{
			h->btsearch_buff[h->btsearch_buff_len - 1] = '\0';
			h->btsearch_buff_len--;
		}
		btsearch_first_search(h);
		if (h->btsearch_list && h->btsearch_list->first)
			btsearch_change_line(line, h, h->btsearch_list->first);
		else
			btsearch_change_line(line, h, NULL);
	}
}
