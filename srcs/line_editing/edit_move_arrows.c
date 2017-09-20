#include "line_editing.h"
#include <stdio.h>

static size_t	get_char_visual_position(t_line *line, char *c)
{
	size_t	index;
	size_t	col_nb;

	col_nb = line->prompt_len;
	index = 0;
	while ((line->buff + index) != c)
	{
		if (col_nb == line->ws_col)
			col_nb = 0;
		else if (*(line->buff + index) == '\n')
			col_nb = 0;
		else
			++col_nb;
		++index;
	}
	return (col_nb);
}

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
	size_t	my_pos;
	size_t	newl_pos;

	newl_pos = 0;
	my_pos = 0;
	newl = NULL;
	if (line->pos < line->ws_col && (newl = newline_on_the_left(line)) == NULL)
		return (0);
	if (newl)
	{
		my_pos = get_char_visual_position(line, line->buff + line->pos);
		newl_pos = get_char_visual_position(line, newl);
	}
	if (my_pos > newl_pos)
	{
		put_termcap("up");
		put_termcap("cr");
		put_ntermcap("nd", newl_pos);
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
	size_t	pos;

	if (line->pos == 0)
		return (0);
	put_termcap("le");
	line->pos--;
	line->old_pos = line->pos;
	if (line->buff[line->pos] == '\n')
	{
		pos = get_char_visual_position(line, line->buff + line->pos);
		put_termcap("up");
		put_ntermcap("nd", pos);
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
