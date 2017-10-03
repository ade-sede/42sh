#include "line_editing.h"

/*
**	Routine used when Ctrl-D is catched.
**	Half of the control is done in get_input.
**	Summary : 
**	- If line is not empty, doesnt do anything.
**	- If line is empty:
**		- If here-document is currently being parsed, ends line editing
**		returning the current input.
**		- Otherwise ouputs a newline and exits.
*/

int		control_d(t_line *line)
{
	if (line->len != 0)
		return (1);
	if (line->heredoc == 1 && line->len != 0)
		return (1);
	(void)line;
	ft_putchar('\n');
	exit(0);
}

char	*control_d_heredoc(t_line *line)
{
	edit_add(4, line);
	return (edit_exit(line));
}
