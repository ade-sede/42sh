#include "line_editing.h"
#include "history.h"

char	*edit_exit(t_line *line)
{
	move_cursor_lastline(line);
	move_cursor_bufflen_from_lastline(line);
	ft_putchar_fd('\n', 2);
	edit_insert_str(line, line->buff + ft_strlen(line->buff) , "\n");
	return (line->buff);
}
