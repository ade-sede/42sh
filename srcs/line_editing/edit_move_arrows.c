#include "line_editing.h"
#include "failure.h"

static ssize_t	newline_on_the_left(t_line *line)
{
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

int		edit_up(t_line *line)
{
	ssize_t	newl;

	newl = -1;
	if (line->pos < line->ws_col && (newl = newline_on_the_left(line)) == -1)
		return (0);
	if (newl != -1)
		line->pos = cursor_goto(line, newl, -1);
	else
		line->pos = cursor_goto(line, line->pos - line->ws_col, -1);
	line->old_pos = line->pos;
	return (1);
}

int		edit_down(t_line *line)
{
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
			logwrite(__func__, "ok\n");
			if (done)
				break ;
			x = 0;
			done = TRUE;
		}
		++count;
	}
	logwrite(__func__, "Objectif was %d\nReached %zu\n", pos.x, x);
	if (x != (size_t)pos.x && !done)
	{
		/* logwrite(__func__, "failed\n"); */
		/* logwrite(__func__, "%d\n", done); */
		return (0);
	}
	line->pos = cursor_goto(line, line->pos + count + 1, -1);
	return (1);
}


int		edit_left(t_line *line)
{
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
	return (1);
}

int		edit_right(t_line *line)
{
	if (line->pos >= line->len)
		return (0);
	if (line->buff[line->pos] == '\n')
		put_termcap("do");
	else if ((((line->prompt_len + line->pos)) % line->ws_col) == line->ws_col - 1)
		put_termcap("do");
	else
		put_termcap("nd");
	line->pos++;
	line->old_pos = line->pos;
	return (1);
}
