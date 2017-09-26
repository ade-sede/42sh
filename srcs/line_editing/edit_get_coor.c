#include "line_editing.h"
#include "failure.h"

/*
**	Takes a pointer to a char situated ON line->buff, and returns its
**	coordinates from the first line of the command (column 0 of line where we
**	display the prompt).
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

size_t	cursor_goto(t_line *line, ssize_t dest_i, ssize_t start_i)
{
	t_coor	pos;
	t_coor	dest;

	if (start_i == -1)
		pos = get_char_visual_coor(line, line->pos);
	else
		pos = get_char_visual_coor(line, start_i);
	dest = get_char_visual_coor(line, dest_i);
	logwrite(__func__, "Pos @ {%d ; %d}\nDest @ {%d ; %d}\n", pos.x, pos.y, dest.x, dest.y);
	if (dest.y > pos.y)
		put_ntermcap("do", (size_t)(dest.y - pos.y));
	else if (pos.y > dest.y)
		put_ntermcap("up", (size_t)(pos.y - dest.y));
	put_termcap("cr");
	put_ntermcap("nd", (size_t)dest.x);
	return ((size_t)dest_i);
}
