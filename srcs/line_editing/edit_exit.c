#ifndef NO_TERMCAPS
#include "line_editing.h"
#include "history.h"

char	*edit_exit(t_line *line)
{
	move_cursor_lastline(line);
	move_cursor_bufflen_from_lastline(line);
	ft_putchar('\n');
	return (line->buff);
}
#endif
