#include "line_editing.h"
#include "failure.h"

/*
**	This function places the cursor both visually and in memory above the
**	characher found at line->buff[dest_i]. The function assumes the cursor is
**	currently well positioned above line->buff[start_i].
*/

ssize_t	cursor_goto_buff(t_line *line, ssize_t dest_i, ssize_t start_i)
{
	t_coor	pos;
	t_coor	dest;

	if (start_i == -1)
		pos = get_char_visual_coor(line, line->pos);
	else
		pos = get_char_visual_coor(line, start_i);
	dest = get_char_visual_coor(line, dest_i);
	/* logwrite(__func__, "Pos @ {%d ; %d}\nDest @ {%d ; %d}\n", pos.x, pos.y, dest.x, dest.y); */ if (dest.y > pos.y)
		put_ntermcap("do", (size_t)(dest.y - pos.y));
	else if (pos.y > dest.y)
		put_ntermcap("up", (size_t)(pos.y - dest.y));
	put_termcap("cr");
	put_ntermcap("nd", (size_t)dest.x);
	return (dest_i);
}


/*
**	Relative takes coordinates of the point relative to where our cursor is
**	Coor takes cooordinates of the point we wanna go to from l0 c0 of this
**	command line (start of the prompt).
**
**	If it is not possible to go to the required coordinates : 
**
** 	if x_pos + x_move > end of line will put the cursor on the last char of the line
** 	if x_pos + x_move < 0 will stay at the start of the line
** 	if y_pos + y_move > last line, will go to last line
** 	if y_pos + y_move < first line (0) , will go to first line
**
** 	Same logic applies to Coor as it calls relative
*/

static int	cursor_goto_x(t_line *line, int x_move, int pos_x)
{
	int		sign;
	int		ret;
	size_t	x;

	ret = 0;
	sign = (x_move < 0) ? -1 : 1;
	x = pos_x;
	while (x_move != 0)
	{
		if (sign == -1 && x == 0)
			break ;
		if (sign == 1 && x == line->ws_col)
			break ;
		if (sign == -1 && (line->pos + ret) == 0)
			break ;
		if (sign == 1 && line->buff[line->pos + ret] == '\n')
			break ;
		ret += 1 * sign;
		x += 1 * sign;
		x_move -= 1 * sign;
	}
	return (ret);
}

static int	cursor_goto_y(t_line *line, int y_move, int pos_x)
{
	int		sign;
	int		ret;
	size_t	x;

	ret = 0;
	sign = (y_move < 0) ? -1 : 1;
	x = pos_x;
	while (y_move)
	{
		logwrite(__func__, MAG"#"CYN"%c"MAG"#\n"RESET, line->buff[line->pos + ret]);//			REMOVE		
		if (sign == -1)
		{
			if (line->pos + ret == 0)
				break ;
			if (x == 0)
				x = line->ws_col;
			if (line->buff[line->pos + ret] == '\n')
			{
				y_move -= 1 * sign;
			}
		}
		x += 1 * sign;
		ret += 1 * sign;
		if (x == (size_t)pos_x)
			break ;
	}
	if (y_move && x != (size_t)pos_x)
		ret += cursor_goto_x(line, x - pos_x, pos_x);
	return (ret);
}

ssize_t	cursor_goto_visual_coor(t_line *line, size_t x, size_t y)
{
	t_coor pos;

	pos = get_char_visual_coor(line, line->pos);
	cursor_goto_visual_relative(line, x - (size_t)pos.x , y - (size_t)pos.y );
	return (0);
}

ssize_t	cursor_goto_visual_relative(t_line *line, int x_move, int y_move)
{
	ssize_t		target;
	t_coor		pos;

	target = -1;
	if (y_move)
	{
		pos = get_char_visual_coor(line, line->pos);
		if (pos.y + y_move > 0)
		{
			target = cursor_goto_y(line, y_move, pos.x);
			line->pos = cursor_goto_buff(line, line->pos + target, -1);
		}
	}
	if (x_move)
	{
		pos = get_char_visual_coor(line, line->pos);
		target = cursor_goto_x(line, x_move, pos.x);
		line->pos = cursor_goto_buff(line, line->pos + target, -1);
	}
	return (line->pos);
}

