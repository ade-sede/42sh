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
	/* logwrite(__func__, "Pos @ {%d ; %d}\nDest @ {%d ; %d}\n", pos.x, pos.y, dest.x, dest.y); */
	if (dest.y > pos.y)
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

static int	cursor_goto_y(t_line *line, int y_move)
{
	t_coor	pos;
	int		sign;
	int		ret;
	size_t	x;

	ret = 0;
	sign = (y_move < 0) ? -1 : 1;
	pos = get_char_visual_coor(line, line->pos);
	x = pos.x;
	while (y_move != 0)
	{
		x += 1 * sign;
		if ((sign == 1 && 1) || (sign == -1 && 1))
			;
		if ((sign == 1 && x == line->ws_col) || (sign == 1 && line->buff[line->pos + ret * sign] == '\n') || (sign == -1 && x == 0))
			y_move -= 1 * sign;
		ret += 1 * sign;
	}
		;
	return (ret);
}

ssize_t	cursor_goto_visual_coor(t_line *line, size_t x, size_t y)
{
	t_coor pos;

	pos = get_char_visual_coor(line, line->pos);
	cursor_goto_visual_relative(line, (int)x - pos.x , (int)y - pos.y );
	/* line->pos = move y */
	/* line->pos = move x */
	return (0);
}

ssize_t	cursor_goto_visual_relative(t_line *line, int x_move, int y_move)
{
	return (0);
}

