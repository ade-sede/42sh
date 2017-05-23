#include "line_editing.h"

t_line		*line(void)
{
	static t_line	s;

	return (&s);
}
