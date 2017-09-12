#include "line_editing.h"

int		control_d(t_line *line)
{
	if (!line->heredoc && line->pos)
	{
	(void)line;
	ft_putchar('\n');
	exit(0);
	}
	return (1);
}
