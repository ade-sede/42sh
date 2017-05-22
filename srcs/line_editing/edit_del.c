#include "line_editing.h"

int	edit_backspace(t_line *line)
{
	if (line->pos == 0)
		return (0);
	ft_memmove((void*)(line->buff + line->pos - 1), (void*)(line->buff + line->pos), line->len - line->pos);
	line->buff[line->len - 1] = '\0';
	line->pos--;
	line->len--;
	return (1);
}
