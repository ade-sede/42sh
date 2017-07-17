/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btsearch_move.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 23:19:54 by vcombey           #+#    #+#             */
/*   Updated: 2017/06/08 23:20:16 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"
#include "history.h"

void	btsearch_change_line(t_line *line, t_hist *h, t_list_d *node)
{
	h->btsearch_cur = node;
	ft_strclr(line->buff);
	ft_strcpy(line->buff, h->btsearch_cur->data);
	line->pos = 0;
	line->len = 0;
}

int	btsearch_next(t_line *line, t_hist *h)
{
	if (h->btsearch_cur && h->btsearch_cur->next)
	{
		btsearch_change_line(line, h, h->btsearch_cur->next);
		return (1);
	}
	return (0);
}

int	btsearch_prev(t_line *line, t_hist *h)
{
	if (h->btsearch_cur && h->btsearch_cur->prev)
	{
		btsearch_change_line(line, h, h->btsearch_cur->prev);
		return (1);
	}
	return (0);
}
