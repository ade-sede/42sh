/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btsearch_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:48 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:17 by ade-sede         ###   ########.fr       */
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
