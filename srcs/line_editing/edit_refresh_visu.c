#include "line_editing.h"
#include "env.h"
#include "failure.h"
#include <stdio.h>

#if 0
void	edit_refresh_visu(t_line *line)
{
	if (line->pos < line->visu_start)
	{
		ft_putnstr_fd(2, line->buff, line->pos);
		ft_putstr("\e[39;42m");
		ft_putnstr_fd(2, line->buff + line->pos, \
				line->visu_start - line->pos);
		ft_putstr("\e[0m");
		ft_putstr_fd(line->buff + line->visu_start, 2);
	}
	else
	{
		ft_putnstr_fd(2, line->buff, line->visu_start);
		ft_putstr("\e[39;42m");
		ft_putnstr_fd(2, line->buff + line->visu_start, \
				line->pos - line->visu_start);
		ft_putstr("\e[0m");
		ft_putstr_fd(line->buff + line->pos, 2);
	}
}
#endif
