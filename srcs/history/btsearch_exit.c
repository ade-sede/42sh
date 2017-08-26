/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btsearch_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 23:19:54 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 01:23:03 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"
#include "history.h"
#include <stdio.h>

int		btsearch_exit(t_line *line, t_hist *h)
{
	if (h->btsearch_list)
	{
		ft_remove_head(&h->btsearch_list, NULL);
		h->btsearch_cur = NULL;
		ft_strclr(h->btsearch_buff);
		h->btsearch_buff_len = 0;
	}
	line->pos = line->len;
	(void)line;
	return (1);
}
