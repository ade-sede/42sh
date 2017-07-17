/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_refresh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 23:19:54 by vcombey           #+#    #+#             */
/*   Updated: 2017/06/08 23:20:20 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

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
** refresh line write buff on multiple lines per ws_col.
*/

void	edit_refresh_line(t_line *line)
{
	size_t	i;
	size_t	ws_col;

	ws_col = line->ws_col;
	ft_putnstr(line->buff, ws_col - line->prompt_len);
	i = ws_col - line->prompt_len;
	while (i < line->len)
	{
		put_termcap("do");
		put_termcap("cr");
		ft_putnstr(line->buff + i, ws_col);
		i += ws_col;
	}
	/*
	**if the cursor is in the last colomn, move it to the next line.
	*/
	if ((line->len + line->prompt_len) % (ws_col) == 0)
		put_termcap("do");
}

size_t	edit_refresh_nchar(t_line *line, size_t padding, char *str, size_t n)
{
	size_t	i;
	size_t	ws_col;

	i = 0;
	ws_col = line->ws_col;
	if (n > ws_col - padding)
	{
		ft_putnstr(str, ws_col - padding);
		i = ws_col - padding;
	}
	while (i + ws_col < n)
	{
		put_termcap("do");
		put_termcap("cr");
		ft_putnstr(str + i, ws_col);
		i += ws_col;
	}
	if (i < n)
	{
		if (n > ws_col - padding)
		{
			put_termcap("do");
			put_termcap("cr");
		}
		ft_putnstr(str + i, n - i);
	}
	/*
	**if the cursor is in the last colomn, move it to the next line.
	*/
	if ((n + padding) % (ws_col) == 0)
		put_termcap("do");
	return ((n + padding) % (ws_col));
}

void	edit_refresh_visu(t_line *line)
{
	size_t start;

	start = line->prompt_len;
	if (line->pos < line->visu_start)
	{
		start = edit_refresh_nchar(line, start, line->buff, line->pos);
		ft_putstr("\e[39;42m");
		start = edit_refresh_nchar(line, start, line->buff + line->pos,  line->visu_start - line->pos);
		ft_putstr("\e[0m");
		start = edit_refresh_nchar(line, start, line->buff + line->visu_start,  line->len - line->visu_start);
	}
	else
	{
		start = edit_refresh_nchar(line, start, line->buff, line->visu_start);
		ft_putstr("\e[39;42m");
		start = edit_refresh_nchar(line, start, line->buff + line->visu_start, line->pos - line->visu_start);
		ft_putstr("\e[0m");
		start = edit_refresh_nchar(line, start, line->buff + line->pos, line->len - line->pos);
	}

}

void	edit_refresh_clear(t_line *line)
{
	put_ntermcap("up", (line->old_pos + line->prompt_len) / line->ws_col);
	put_termcap("cr");
	//put_ntermcap("dl", init_line);
	put_termcap("cd");
	//put_termcap("do");
}

void	edit_refresh(t_line *line)
{
	//ft_putchar('\n');
	//put_termcap("up");
	edit_refresh_clear(line);
	//put_termcap("do");
	//put_termcap("dl");
	line->prompt_len = put_prompt(NULL);
	line->visu_mode ? edit_refresh_visu(line) : edit_refresh_line(line);
	edit_refresh_cursor(line);
}
