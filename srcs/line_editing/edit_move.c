/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:37 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:33 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

/*
**	Moves to the closest space to the left
*/

int		edit_word_left(t_line *line)
{
	if (line->pos > 0 && line->buff[line->pos] == '\0')
		edit_left(line);
	while (line->pos > 0 && line->buff[line->pos] == ' ')
		edit_left(line);
	while (line->pos > 0 && line->buff[line->pos] != ' ')
		edit_left(line);
	return (1);
}

/*
**	Moves to the closest space to the right
*/

int		edit_word_right(t_line *line)
{
	while (line->pos < line->len && line->buff[line->pos] == ' ')
		edit_right(line);
	while (line->pos < line->len && line->buff[line->pos] \
			&& line->buff[line->pos] != ' ')
		edit_right(line);
	return (1);
}

/*
**	Moves to the start of the first line of input.
*/

int		edit_home(t_line *line)
{
	line->pos = cursor_goto_buff(line, 0, line->pos);
	if (line->visu_mode)
	{
		line->old_pos = line->pos;
		edit_refresh(line);
	}
	return (1);
}

/*
**	Moves to the start of the last line of input.
*/

int		edit_end(t_line *line)
{
	line->pos = cursor_goto_buff(line, line->len, line->pos);
	if (line->visu_mode)
	{
		line->old_pos = line->pos;
		edit_refresh(line);
	}
	return (1);
}
