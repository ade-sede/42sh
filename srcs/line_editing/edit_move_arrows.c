#include "line_editing.h"
#include <stdio.h>

static char	*newline_on_the_left(t_line *line)
{
	char	old_char;
	char	*newl;

	old_char = line->buff[line->pos];
	line->buff[line->pos] = 0;
	newl = ft_strrchr(line->buff, '\n');
	line->buff[line->pos] = old_char;
	return (newl);
}

int		edit_up(t_line *line)
{
	char	*newl;
	size_t	pos_x;
	size_t	newl_x;

	newl_x = 0;
	pos_x = 0;
	newl = NULL;
	if (line->pos < line->ws_col && (newl = newline_on_the_left(line)) == NULL)
		return (0);
	if (newl)
	{
		pos_x = (size_t)get_char_visual_coor(line, line->buff + line->pos).x;
		newl_x = (size_t)get_char_visual_coor(line, newl).x;
	}
	if (pos_x > newl_x)
	{
		put_termcap("up");
		put_termcap("cr");
		put_ntermcap("nd", newl_x);
		line->pos = (line->buff + line->pos) - newl;
	}
	else
	{
		put_termcap("up");
		line->pos -= line->ws_col;
		line->old_pos = line->pos;
	}
	return (1);
}

int		edit_down(t_line *line)
{
	size_t	i;
	size_t	n;

	if (line->pos + line->ws_col > line->len)
		return (0);
	if (line->buff[line->pos] == '\n')
		return (0);
	n = line->ws_col;
	i = 0;
	while (i++ < line->ws_col)
		edit_right(line);
	line->old_pos = line->pos;
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
		pos_x = (size_t)get_char_visual_coor(line, line->buff + line->pos).x;
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
