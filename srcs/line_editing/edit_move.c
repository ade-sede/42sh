#include "line_editing.h"

int		edit_word_left(t_line *line)
{
	if (line->pos > 0 && line->buff[line->pos] == '\0')
		edit_left(line);
	while (line->pos > 0 && line->buff[line->pos] == ' ')
		edit_left(line);
	while (line->pos > 0 && line->buff[line->pos] != ' ')
		edit_left(line);
	return (1);
}

int		edit_word_right(t_line *line)
{
	while (line->pos < line->len && line->buff[line->pos] == ' ')
		edit_right(line);
	while (line->pos < line->len && line->buff[line->pos] \
			&& line->buff[line->pos] != ' ')
		edit_right(line);
	return (1);
}

int		edit_home(t_line *line)
{
	while (1)
		if (!edit_left(line))
			break ;
	return (1);
}

int		edit_end(t_line *line)
{
	while (line->pos < line->len)
		edit_right(line);
	return (1);
}
