#include "history.h"
#include "line_editing.h"

unsigned long	history_move_loop(t_line *line)
{
	unsigned long	keycode;
	t_hist		*h;

	h = singleton_hist();
	history_move_init(line, h);
	while (42)
	{
		keycode = 0;
		read(0, &keycode, 8);
		if (keycode == KEY_UP)
			history_next(line, h);
		else if (keycode == KEY_DOWN)
			history_prev(line, h);
		else
		{
			history_move_exit(line, h);
			return (keycode);
		}
		edit_refresh(line);
	}
}
