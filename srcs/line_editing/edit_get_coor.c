#include "line_editing.h"
#include "failure.h"

/*
**	Takes the position of a char situated ON line->buff, and returns its
**	coordinates from the first line of the command (column 0 of line where we
**	display the prompt (line0)).
*/

t_coor	get_char_visual_coor(t_line *line, ssize_t pos)
{
	size_t	index;
	int		x;
	int		y;

	index = 0;
	x = line->prompt_len;
	y = 0;
	while ((ssize_t)index != pos && line->buff[index] != 0)
	{
		++x;
		if (x == (int)line->ws_col || line->buff[index] == '\n')
		{
			x = 0;
			++y;
		}
		++index;
	}
	return ((t_coor){x, y});
}
