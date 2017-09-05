#ifndef NO_TERMCAPS
#include "line_editing.h"

int	enter_visual_mode(t_line *line)
{
	line->visu_mode = 1;
	line->visu_start = line->pos;
	return (1);
}

int	copy(t_line *line)
{
	if (line->visu_mode)
	{
		if (line->visu_start < line->pos)
			line->copied_text = ft_strndup(line->buff + line->visu_start, \
					line->pos - line->visu_start);
		else if (line->visu_start > line->pos)
			line->copied_text = ft_strndup(line->buff + line->pos, \
					line->visu_start - line->pos);
		line->visu_mode = 0;
	}
	return (1);
}

int	paste(t_line *line)
{
	if (line->copied_text)
		edit_insert_str(line, line->buff + line->pos, line->copied_text);
	return (1);
}
#endif
