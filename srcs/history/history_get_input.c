#include "history.h"
#include "libft.h"
#include "shopt.h"
#include "line_editing.h"
#include <stdio.h>

int		history_get_input(t_line *line, t_history *history, unsigned long keycode)
{
	if (keycode == KEY_UP || keycode == KEY_DOWN)
	{
		if (!history->target && singleton_env()->option & OZSHHIST)
			history->target = ft_strdup(line->buff);
		if (keycode == KEY_UP)
			history_prev(line, history);
		else if (keycode == KEY_DOWN)
			history_next(line, history);
		return (1);
	}
	else if (history->target && singleton_env()->option & OZSHHIST)
			ft_strdel(&history->target);
	return (0);
}
