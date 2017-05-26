#include "line_editing.h"

t_line		*singleton_line(void)
{
	static t_line	s;

	return (&s);
}

void		edit_line_init(t_line *line)
{
	ft_bzero(line->buff, line->len);
	line->visu_mode = 0;
	line->pos = 0;
	line->len = 0;
}
