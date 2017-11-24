/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btsearch_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:36 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:18 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

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
