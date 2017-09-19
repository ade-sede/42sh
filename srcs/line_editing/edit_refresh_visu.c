#include "line_editing.h"
#include "env.h"

void	edit_refresh_nchar_2(size_t n, size_t *i, char *str, size_t ws_col)
{
	while (*i + ws_col < n)
	{
		put_termcap("do");
		put_termcap("cr");
		ft_putnstr_fd(2, str + *i, ws_col);
		*i += ws_col;
	}
}

size_t	edit_refresh_nchar(t_line *line, size_t padding, char *str, size_t n)
{
	size_t	i;
	size_t	ws_col;

	i = 0;
	ws_col = line->ws_col;
	if (n > ws_col - padding)
	{
		ft_putnstr_fd(2, str, ws_col - padding);
		i = ws_col - padding;
	}
	edit_refresh_nchar_2(n, &i, str, ws_col);
	if (i < n)
	{
		if (n > ws_col - padding)
		{
			put_termcap("do");
			put_termcap("cr");
		}
		ft_putnstr_fd(2, str + i, n - i);
	}
	if ((n + padding) % (ws_col) == 0)
		put_termcap("do");
	return ((n + padding) % (ws_col));
}

void	edit_refresh_visu(t_line *line)
{
	if (line->pos < line->visu_start)
	{
		ft_putnstr_fd(2, line->buff, line->pos);
		ft_putstr("\e[39;42m");
		ft_putnstr_fd(2, line->buff + line->pos, \
				line->visu_start - line->pos);
		ft_putstr("\e[0m");
		ft_putnstr_fd(2, line->buff + line->visu_start, \
				line->len - line->visu_start);
	}
	else
	{
		ft_putnstr_fd(2, line->buff, line->visu_start);
		ft_putstr("\e[39;42m");
		ft_putnstr_fd(2, line->buff + line->visu_start, \
				line->pos - line->visu_start);
		ft_putstr("\e[0m");
		ft_putnstr_fd(2, line->buff + line->pos, \
				line->len - line->pos);
	}
}
