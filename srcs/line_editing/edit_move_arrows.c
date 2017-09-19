/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_move_arrows.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:50 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:26 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

int		edit_up(t_line *line)
{
	if (line->pos < line->ws_col)
		return (0);
	put_termcap("up");
	line->pos -= line->ws_col;
	line->old_pos = line->pos;
	return (1);
}

int		edit_down(t_line *line)
{
	size_t	i;
	size_t	n;

	if (line->pos + line->ws_col > line->len)
		return (0);
	n = line->ws_col;
	i = 0;
	while (i++ < line->ws_col)
		edit_right(line);
	line->old_pos = line->pos;
	return (1);
}

int		edit_left(t_line *line)
{
	if (line->pos == 0)
		return (0);
	put_termcap("le");
	line->pos--;
	line->old_pos = line->pos;
	return (1);
}

int		edit_right(t_line *line)
{
	if (line->pos >= line->len)
		return (0);
	if ((((line->prompt_len + line->pos)) % line->ws_col) == line->ws_col - 1)
		put_termcap("do");
	else
		put_termcap("nd");
	line->pos++;
	line->old_pos = line->pos;
	return (1);
}
