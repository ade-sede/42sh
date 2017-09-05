#ifndef NO_TERMCAPS
#include "history.h"
#include "line_editing.h"

int		history_get_input(t_line *line, unsigned long keycode, int *history)
{
	t_hist			*h;

	h = singleton_hist();
	if (keycode == KEY_UP || keycode == KEY_DOWN)
	{
		if (!(*history))
		{
			history_move_init(line, h);
			*history = 1;
		}
		if (keycode == KEY_UP)
			history_next(line, h);
		else if (keycode == KEY_DOWN)
			history_prev(line, h);
		return (1);
	}
	else if (*history)
	{
		*history = 0;
		history_move_exit(line, h);
		return (0);
	}
	return (0);
}
#endif
