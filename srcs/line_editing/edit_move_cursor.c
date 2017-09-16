/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_move_cursor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 22:41:02 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/16 02:27:01 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

void	move_cursor_lastline(t_line *line)
{
	put_ntermcap("do", ((line->len - 1 + line->prompt_len) / line->ws_col) \
			- (line->pos + line->prompt_len) / line->ws_col);
	put_termcap("cr");
}

void	move_cursor_lastline_from_first_line(t_line *line)
{
	put_ntermcap("do", ((line->len - 1 + line->prompt_len) / line->ws_col) \
			- (0 + line->prompt_len) / line->ws_col);
	put_termcap("cr");
}

void	move_cursor_firstline_from_lastline(t_line *line)
{
	put_ntermcap("up", ((line->len - 1 + line->prompt_len) / line->ws_col) \
			- (line->prompt_len) / line->ws_col);
	put_termcap("cr");
}

void	move_cursor_firstline_from_prev_pos(t_line *line)
{
	put_ntermcap("up", ((line->old_pos - 1 + line->prompt_len) / line->ws_col) \
			- (line->prompt_len) / line->ws_col);
	put_termcap("cr");
}

void	move_cursor_bufflen_from_lastline(t_line *line)
{
	put_termcap("cr");
	put_ntermcap("nd", (line->len + line->prompt_len) % (line->ws_col));
}
