/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btsearch_signals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 22:41:02 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/16 02:27:01 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include "line_editing.h"
#include <signal.h>

int		btsearch_handle_sigwinch(t_line *line, t_hist *h)
{
	(void)line;
	(void)h;
	return (1);
}

void	btsearch_handle_sigint(int keycode)
{
	t_line	*line;
	t_hist	*h;

	(void)keycode;
	line = singleton_line();
	h = singleton_hist();
	btsearch_exit(line, h);
	line->btsearch = 0;
	h->signum = 0;
	ft_strclr(line->buff);
	line->len = 0;
	line->pos = 0;
	edit_set_signals();
	edit_refresh(singleton_line());
}

void	btsearch_set_btsearch_signum(int num)
{
	singleton_hist()->signum = num;
}

void	btsearch_handle_signals(void)
{
	signal(SIGINT, &btsearch_handle_sigint);
}
