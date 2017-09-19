/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_paste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:50 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:24 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

int	enter_visual_mode(t_line *line)
{
	line->visu_mode = 1;
	line->visu_start = line->pos;
	return (1);
}

int	copy(t_line *line)
{
	if (line->visu_mode)
	{
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

int	paste(t_line *line)
{
	if (line->copied_text)
	{
		edit_insert_str(line, line->buff + line->pos, line->copied_text);
		edit_refresh(line);
	}
	return (1);
}
