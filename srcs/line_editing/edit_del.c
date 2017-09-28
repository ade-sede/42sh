#include "line_editing.h"
#include "failure.h"

int	edit_backspace(t_line *line)
{
	/* size_t	s; */

	if (line->pos == 0)
		return (0);
	ft_memmove((void*)(line->buff + line->pos - 1), \
			(void*)(line->buff + line->pos), line->len - line->pos);
	line->buff[line->len - 1] = '\0';
	line->pos--;
	line->len--;

t_coor pos;
t_coor old_pos;

pos = get_char_visual_coor(line, line->pos);
old_pos = get_char_visual_coor(line, line->old_pos);
	logwrite(PNK"AFTER BACKSPACE"RESET, "Pos = {%d ; %d}\nOld_pos = {%d ; %d}\n", pos.x ,pos.y, old_pos.x, old_pos.y);
	edit_refresh(line);
	return (1);
}
