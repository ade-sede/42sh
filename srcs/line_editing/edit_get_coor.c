#include "line_editing.h"
#include "failure.h"

/*
**	Gives the visual offset of the prompt's last char from
**	the first char of the prompt.
*/

#include <stdio.h>
#include "line_editing.h"

t_coor			get_prompt_visual_offset(t_line *line)
{
	size_t	x;
	size_t	y;

	x = line->prompt_len % (line->ws_col);
	y = line->prompt_len / (line->ws_col);
	return ((t_coor){(int)x, (int)y});
}

/*
**	Takes the position of a char situated ON line->buff, and returns its
**	coordinates from the first line of the command (column 0 of line where we
**	display the prompt (line0)). Skipping prompt on first line.
*/

t_coor			get_char_visual_coor(t_line *line, ssize_t pos)
{
	size_t	index;
	int		x;
	int		y;

	index = 0;
	x = get_prompt_visual_offset(line).x;
	y = 0;
	while ((ssize_t)index != pos)
	{
		if (line->buff[index] == '\t')
			x += (x % 8) ? (8 - (x % 8)) : (8);
		else
			++x;
		if (x >= (int)line->ws_col || line->buff[index] == '\n')
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

static void		first_lopp(t_line *line, size_t *ret, size_t *x, size_t *y)
{
	if (line->buff[*ret] == '\t')
		*x += ((*x) % 8) ? (8 - ((*x) % 8)) : (8);
	else
		++(*x);
	if ((*x) == line->ws_col || line->buff[*ret] == '\n')
	{
		++(*y);
		(*x) = 0;
	}
	++(*ret);
}

size_t			get_char_mem_coor(size_t ret, t_line *line, size_t x_target,
		size_t y_target)
{
	size_t	x;
	size_t	y;
	t_coor	pos;

	pos = get_char_visual_coor(line, 0);
	x = pos.x;
	y = pos.y;
	while (y != y_target && line->buff[ret])
		first_lopp(line, &ret, &x, &y);
	while (x != x_target)
	{
		if (x >= line->ws_col || line->buff[ret] == '\n' || ret >= line->len)
		{
			if (x > line->ws_col)
				x = line->ws_col;
			break ;
		}
		if (line->buff[ret] == '\t')
			x += (x % 8) ? (8 - (x % 8)) : (8);
		else
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

size_t			get_char_mem_coor_relative(t_line *line, int x_move, int y_move)
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
		ret = get_char_mem_coor(0, line, x, y);
		check_ret = get_char_visual_coor(line, ret);
		if (y_move != 0 && check_ret.y == pos.y)
			return (line->pos);
		if (y_move < 0 && check_ret.y > pos.y)
			return (line->pos);
	}
	return (ret);
}
