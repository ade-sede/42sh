#include "line_editing.h"
#include "history.h"

/*
**	Exit routine.
**	Moves cursor to the end of the input, insert a newline to the end of
**	the buffer Returns the address of the buffer.
*/

char	*edit_exit(t_line *line)
{
	move_cursor_lastline(line);
	move_cursor_bufflen_from_lastline(line);
	append_char_hist_cmd_node(get_cmd_node(singleton_history()->current->data), '\n');
	/* edit_insert_str(line, line->buff + ft_strlen(line->buff), "\n"); */
	// REMOVE THIS, tmp change
	line->buff = ft_strchange(line->buff, ft_strjoin(line->buff, "\n"));
	ft_putchar_fd('\n', 2);
	return (line->buff);
}
