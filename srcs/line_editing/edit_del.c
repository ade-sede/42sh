#include "line_editing.h"
#include "failure.h"

int	edit_backspace(t_line *line)
{
	if (line->pos == 0)
		return (0);
	edit_refresh_clear(line);
	ft_memmove((void*)(line->buff + line->pos - 1), \
			(void*)(line->buff + line->pos), line->len - line->pos);
	line->buff[line->len - 1] = '\0';
	line->pos--;
	line->len--;
	put_prompt(line);
	line->visu_mode ? edit_refresh_visu(line) : edit_refresh_line(line);
	edit_refresh_cursor(line);
	return (1);
}
