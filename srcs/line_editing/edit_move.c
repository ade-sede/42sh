/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 23:19:54 by vcombey           #+#    #+#             */
/*   Updated: 2017/06/08 23:20:20 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

int		edit_left(t_line *line)
{
	if (line->pos > 0)
		line->pos--;
	return (1);
}

int		edit_right(t_line *line)
{
	if (line->pos < line->len)
		line->pos++;
	return (1);
}

int		edit_word_left(t_line *line)
{
	if (line->pos > 0 && line->buff[line->pos] == '\0')
		line->pos--;
	while (line->pos > 0 && line->buff[line->pos] == ' ')
		line->pos--;
	while (line->pos > 0 && line->buff[line->pos] != ' ')
		line->pos--;
	return (1);
}

int		edit_up(t_line *line)
{
	if (line->pos >= line->ws_col)
		line->pos -= line->ws_col;
	return (1);
}

int		edit_down(t_line *line)
{
	if (line->pos + line->ws_col <= line->len)
		line->pos += line->ws_col;
	return (1);
}

int		edit_word_right(t_line *line)
{
	while (line->pos < line->len && line->buff[line->pos] == ' ')
		line->pos++;
	while (line->pos < line->len && line->buff[line->pos] && line->buff[line->pos] != ' ')
		line->pos++;
	return (1);
}

int		edit_home(t_line *line)
{
	line->pos = 0;
	return (1);
}

int		edit_end(t_line *line)
{
	line->pos = line->len;
	return (1);
}
