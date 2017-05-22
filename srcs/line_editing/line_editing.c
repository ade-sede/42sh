#include "line_editing.h"

t_line		*line(void)
{
	static t_line	s;

	return (&s);
}

void	edit_add(int keycode, t_line *line)
{
	if (line->pos == line->len - 1)
		line->buff[line->len] = (char)keycode;
	else
	{
		ft_memmove((void*)(line->buff + line->pos + 1), (void*)(line->buff + line->pos), line->len - line->pos);
		line->buff[line->pos] = (char)keycode;
	}
	line->pos++;
	line->len++;
}
