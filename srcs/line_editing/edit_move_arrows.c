#include "line_editing.h"
#include "failure.h"

#if 0
static ssize_t	newline_on_the_left(t_line *line) {
	char	old_char;
	ssize_t	newl;
	size_t	i;

	i = 0;
	old_char = line->buff[line->pos];
	line->buff[line->pos] = 0;
	newl = ft_strrichr(line->buff, '\n');
	line->buff[line->pos] = old_char;
	while (newl + i != line->pos)
		++i;
	if (i >= line->ws_col)
		newl = -1;
	return (newl);
}
#endif

int		edit_up(t_line *line)
{
#if 0
	size_t	x;
	size_t	count;
	ssize_t	newl;
	t_coor	pos;
	t_coor	curs;
	int		done;

	done = FALSE;
	newl = -1;
	pos = get_char_visual_coor(line, line->pos);
	x = pos.x;
	count = 0;
	if (pos.y == 0)
		return (0);
	while (--x != (size_t)pos.x)
	{
		logwrite(__func__, MAG"#"CYN"%c @ %d with x = %zu"MAG"#\n"RESET, line->buff[line->pos - count], line->pos - count, x);
		if (x == 0)
			x = line->ws_col;
		if (line->pos - (count + 1) == 0)
			break ;
		if (line->buff[line->pos - count] == '\n')
		{
			if (done)
				break ;
			newl = count;
			curs = get_char_visual_coor(line, line->pos - count);
			x = curs.x;
			done = TRUE;
		}
		++count;
	}
	logwrite(__func__, "After loop : x = %zu\nExpected was %zu\nnewl = %zu\n", x, pos.x, newl);
	if (x != (size_t)pos.x)
		count = newl;
	line->pos = cursor_goto_buff(line, line->pos - count, -1);
	line->old_pos = line->pos;
	return (1);
#endif
	line->pos = cursor_goto_visual_relative(line, 0, -1);
	line->old_pos = line->pos;
	return (0);
}

int		edit_down(t_line *line)
{
#if 0
	size_t	x;
	size_t	count;
	int		done;
	t_coor	pos;

	done = FALSE;
	pos = get_char_visual_coor(line, line->pos);
	x = pos.x;
	count = 0;
	while (++x != (size_t)pos.x)
	{
		if (x == line->ws_col)
			x = 0;
		if (line->buff[line->pos + count + 1] == 0)
			break ;
		if (line->buff[line->pos + count] == '\n')
		{
			if (done)
				break ;
			x = 0;
			done = TRUE;
		}
		++count;
	}
	if (x > (size_t)pos.x && !done)
		return (0);
	line->pos = cursor_goto_buff(line, line->pos + count + 1, -1);
	line->old_pos = line->pos;
	return (1);
#endif
	line->pos = cursor_goto_visual_relative(line, 0, 1);
	line->old_pos = line->pos;
	return (0);
}


int		edit_left(t_line *line)
{
#if 0
	size_t	pos_x;

	if (line->pos == 0)
		return (0);
	put_termcap("le");
	line->pos--;
	line->old_pos = line->pos;
	if (line->buff[line->pos] == '\n')
	{
		pos_x = (size_t)get_char_visual_coor(line, line->pos).x;
		put_termcap("up");
		put_ntermcap("nd", pos_x);
	}
#endif
	if (line->pos == 0)
		return (0);
	line->pos = cursor_goto_buff(line, line->pos - 1, -1);
	line->old_pos = line->pos;
	return (1);
}

int		edit_right(t_line *line)
{
	if (line->pos >= line->len)
		return (0);
#if 0
	if (line->buff[line->pos] == '\n')
		put_termcap("do");
	else if ((((line->prompt_len + line->pos)) % line->ws_col) == line->ws_col - 1)
		put_termcap("do");
	else
		put_termcap("nd");
	line->pos++;
#endif
	line->pos = cursor_goto_buff(line, line->pos + 1, -1);
	line->old_pos = line->pos;
	return (1);
}
