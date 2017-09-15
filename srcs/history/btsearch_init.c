/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btsearch_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 22:41:03 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/15 22:41:13 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"
#include "history.h"

int		btsearch_init(t_line *line, t_hist *h)
{
	ft_strclr(h->btsearch_buff);
	h->btsearch_buff_len = 0;
	h->btsearch_list = NULL;
	h->btsearch_cur = NULL;
	edit_refresh_clear(line);
	ft_strclr(line->buff);
	line->len = 0;
	line->pos = 0;
	(void)h;
	return (1);
}
