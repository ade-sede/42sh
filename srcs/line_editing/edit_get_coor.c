/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_get_coor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 12:00:47 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/21 18:04:23 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

/*
**	Takes a pointer to a char situated ON line->buff, and returns its
**	coordinates from the first line of the command (column 0 of line where we
**	display the prompt).
*/

t_coor	get_char_visual_coor(t_line *line, char *c)
{
	size_t	index;
	int		x;
	int		y;

	index = 0;
	x = line->prompt_len;
	y = 0;
	while ((line->buff + index) != c)
	{
		x++;
		if (x == (int)line->ws_col|| line->buff[index] == '\n')
		{
			x = 0;
			++y;
		}
		++index;
	}
	return ((t_coor){x, y});
}
