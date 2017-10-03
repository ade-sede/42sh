#include "line_editing.h"
#include "failure.h"

/*
**	Takes the position of a char situated ON line->buff, and returns its
**	coordinates from the first line of the command (column 0 of line where we
**	display the prompt (line0)). Skipping prompt on first line.
*/

t_coor	get_char_visual_coor(t_line *line, ssize_t pos)
{
	size_t	index;
	int		x;
	int		y;

	index = 0;
	x = line->prompt_len;
	y = 0;
	while ((ssize_t)index != pos)
	{
		++x;
		if (x == (int)line->ws_col || line->buff[index] == '\n')
		{
			x = 0;
			++y;
		}
		++index;
		if (line->buff[index] == 0)
			break ;
	}
	return ((t_coor){x, y});
}

/*
**	Returns the index of the char that fits the most the coordinates {x ; y}
**	(Index from the start of the prompt).
*/

size_t	get_char_mem_coor(t_line *line, size_t x_target, size_t y_target)
{
	size_t	x;
	size_t	y;
	t_coor	pos;
	size_t	ret;

	pos = get_char_visual_coor(line, 0);
	x = pos.x;
	y = pos.y;
	ret = 0;
	while (y != y_target && line->buff[ret])
	{
		++x;
		if (x == line->ws_col || line->buff[ret] == '\n')
		{
			++y;
			x = 0;
		}
		++ret;
	}
	while (x != x_target)
	{
		if (x == line->ws_col || line->buff[ret] == '\n' || ret >= line->len)
			break;
		++x;
		++ret;
	}
	return (ret);
}

/*
**	Computes the absolute coordinates of the destination according the the
**	moves requested, sends it to get_char_mem_coor. If the result is
**	inconsistant with the input, returns the current line->pos (equivalent to
**	not doing anything).
*/

size_t	get_char_mem_coor_relative(t_line *line, int x_move, int y_move)
{
	t_coor	pos;
	size_t	ret;
	size_t	x;
	size_t	y;
	t_coor	check_ret;

	ret = 0;
	pos = get_char_visual_coor(line, line->pos);
	x = (size_t)pos.x + x_move;
	y = (size_t)pos.y + y_move;
	if (x <= line->ws_col)
	{
		ret = get_char_mem_coor(line, x, y);
		check_ret = get_char_visual_coor(line, ret);
		if (y_move != 0 && check_ret.y == pos.y)
			return (line->pos);
		if (y_move < 0 && check_ret.y > pos.y)
			return (line->pos);
	}
	return (ret);
}
