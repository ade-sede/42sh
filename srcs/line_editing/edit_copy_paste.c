/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_copy_paste.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:37 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:31 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

/*
**	Every function related to the copy-paste mechanics.
*/

/*
**	Toggles the visual_mode flag, line->visu_start records the index when the
**	option is toggled.
*/

int	enter_visual_mode(t_line *line)
{
	if (line->visu_mode)
	{
		line->visu_mode = 0;
		edit_refresh(line);
	}
	else
	{
		line->visu_mode = 1;
		line->visu_start = line->pos;
	}
	return (1);
}

/*
**	Copies the highlighted text into an internal buffer.  This text runs from
**	line->visu_start to line->pos, or line->pos to line->visu start if we move
**	backwards after entering visual_mode
*/

int	copy(t_line *line)
{
	if (line->visu_mode)
	{
		if (line->copied_text)
			free(line->copied_text);
		if (line->visu_start < line->pos)
			line->copied_text = ft_strndup(line->buff + line->visu_start, \
					line->pos - line->visu_start);
		else if (line->visu_start > line->pos)
			line->copied_text = ft_strndup(line->buff + line->pos, \
					line->visu_start - line->pos);
		line->visu_mode = 0;
		edit_refresh(line);
	}
	return (1);
}

/*
**	Insert the copied text into the buffer.
*/

int	paste(t_line *line)
{
	if (line->copied_text)
	{
		edit_insert_str(line, line->buff + line->pos, line->copied_text);
		edit_refresh(line);
	}
	return (1);
}
