#include "line_editing.h"

int		edit_left(t_line *line)
{
	if (line->pos > 0)
		line->pos--;
}

int		edit_right(t_line *line)
{
	if (line->pos < line->len)
		line->pos++;
}

int		edit_home(t_line *line)
{
	if (keycode == KEY_HOME)
		line->pos = 0;
}

int		edit_end(t_line *line)
{
	if (keycode == KEY_END)
		line->pos = line->len;
}

