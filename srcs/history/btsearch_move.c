/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btsearch_move.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:36 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:19 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

void	btsearch_change_line(t_line *line, t_hist *h, t_list_d *node)
{
	h->btsearch_cur = node;
	ft_strclr(line->buff);
	line->len = 0;
	line->pos = 0;
	if (h->btsearch_cur)
	{
		edit_insert_str(line, line->buff, h->btsearch_cur->data);
		line->pos = ft_strstr(line->buff, h->btsearch_buff) - line->buff;
		line->len = ft_strlen(line->buff);
	}
}

int		btsearch_next(t_line *line, t_hist *h)
{
	if (h->btsearch_cur && h->btsearch_cur->next)
	{
		btsearch_change_line(line, h, h->btsearch_cur->next);
		return (1);
	}
	return (0);
}

int		btsearch_prev(t_line *line, t_hist *h)
{
	if (h->btsearch_cur && h->btsearch_cur->prev)
	{
		btsearch_change_line(line, h, h->btsearch_cur->prev);
		return (1);
	}
	return (0);
}
