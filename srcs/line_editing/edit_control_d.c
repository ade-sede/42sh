#include "line_editing.h"

/*
**	When CTRL-D is read, if the line is empty :
**	- if we're on the main LE, exit.
**	- if we're on heredoc LE, terminate le, return line->buff.
**
**	If line isnt empty, delete, delete char under the cursor if it exists.
*/

int		control_d(t_line *line)
{
	if (line->len == 0)
	{
		ft_putchar('\n');
		exit(0);
	}
	if (line->pos != line->len)
	{
		ft_memmove((void*)(line->buff + line->pos), (void*)(line->buff + line->pos + 1), line->len - line->pos + 1);
		line->len--;
		edit_refresh(line);
	}
	return (1);
}

char	*control_d_heredoc(t_line *line)
{
	edit_add(4, line);
	return (edit_exit(line));
}
