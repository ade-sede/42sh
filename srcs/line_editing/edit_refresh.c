/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_refresh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 05:07:29 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/28 17:03:22 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"
#include "env.h"

void	edit_refresh_cursor(t_line *line)
{
	size_t	src_col;
	size_t	src_line;
	size_t	dest_line;
	size_t	dest_col;
	size_t	ws_col;

	ws_col = line->ws_col;
	src_col = (line->len + line->prompt_len) % (ws_col);
	dest_col = (line->pos + line->prompt_len) % (ws_col);
	src_line = (line->len + line->prompt_len) / (ws_col);
	dest_line = (line->pos + line->prompt_len) / (ws_col);
	put_ntermcap("up", src_line - dest_line);
	if (dest_col > src_col)
		put_ntermcap("nd", dest_col - src_col);
	else
		put_ntermcap("le", src_col - dest_col);
}

/*
** Refresh line write buff on multiple lines per ws_col.  If the cursor is in
** the last colomn, move it to the next line.
*/

void	edit_refresh_line(t_line *line)
{
	ft_putstr(line->buff);
	if ((((line->prompt_len + line->pos)) % line->ws_col) == line->ws_col - 1)
		put_termcap("do");
}

void	edit_refresh_clear(t_line *line)
{
	put_ntermcap("up", (line->old_pos + line->prompt_len) / line->ws_col);
	put_termcap("cr");
	put_termcap("cd");
}

void	edit_refresh(t_line *line)
{
	edit_refresh_clear(line);
	put_prompt(line);
	line->visu_mode ? edit_refresh_visu(line) : edit_refresh_line(line);
	edit_refresh_cursor(line);
}
