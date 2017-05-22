#include "line_editing.h"

int		edit_left(t_line *line)
{
	if (line->pos > 0)
		line->pos--;
	return (1);
}

int		edit_right(t_line *line)
{
	if (line->pos < line->len)
		line->pos++;
	return (1);
}

int		edit_home(t_line *line)
{
	line->pos = 0;
	return (1);
}

int		edit_end(t_line *line)
{
	line->pos = line->len;
	return (1);
}

