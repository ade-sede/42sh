/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btsearch_refresh.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 23:19:54 by vcombey           #+#    #+#             */
/*   Updated: 2017/06/08 23:20:17 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"
#include "history.h"

void	btsearch_refresh(t_line *line, t_hist *h)
{
	edit_refresh_clear(line);
	move_cursor_lastline(line);
	ft_putchar('\n');
	(h->btsearch_list == NULL || h->btsearch_list->first == NULL) ? ft_putstr("failing bck-i-search: ") : ft_putstr("bck-i-search: ");
	ft_putstr(h->btsearch_buff);
	ft_putchar('_');
	put_termcap("up");
	move_cursor_firstline_from_lastline(line);
	line->prompt_len = put_prompt(singleton_env());
	edit_refresh_line(line);
	edit_refresh_cursor(line);
	(void)h;
}
