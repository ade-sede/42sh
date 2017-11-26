/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:36 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:20 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

int		strnequ_writen_buff(void *data)
{
	int len;

	len = ft_strlen(singleton_hist()->writen_buff);
	if (len == 0)
		return (1);
	if (ft_strnequ(data, singleton_hist()->writen_buff, len))
		return (1);
	return (0);
}

int		history_next(t_line *line, t_hist *h)
{
	t_list_d	*tmp;

	if (!h->list || !h->list->first)
		return (0);
	tmp = NULL;
	tmp = ft_double_lst_return_if((h->cur) ? h->cur->next : h->list->first, \
			strnequ_writen_buff, 1);
	if (tmp)
	{
		h->cur = tmp;
		history_line_refresh(line, h->cur->data);
	}
	else
		put_termcap("bl");
	return (1);
}

int		history_prev(t_line *line, t_hist *h)
{
	t_list_d	*tmp;

	if (!h->list || !h->list->first)
		return (0);
	tmp = NULL;
	tmp = ft_double_lst_return_if((h->cur) ? h->cur->prev : NULL, \
			strnequ_writen_buff, 2);
	if (tmp)
	{
		h->cur = tmp;
		history_line_refresh(line, h->cur->data);
	}
	else
	{
		put_termcap("bl");
		line->pos = ft_strlen(h->writen_buff);
		edit_refresh(line);
	}
	return (1);
}

int		history_move_init(t_line *line, t_hist *h)
{
	if (h->writen_buff)
		ft_strcpy(h->writen_buff, line->buff);
	return (1);
}

int		history_move_exit(t_line *line, t_hist *h)
{
	ft_strclr(h->writen_buff);
	(void)line;
	return (1);
}
