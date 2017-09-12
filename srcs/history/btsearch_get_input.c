#ifndef NO_TERMCAPS
#include "line_editing.h"
#include "history.h"

int		btsearch_get_input(t_line *line, unsigned long keycode)
{
	t_hist				*h;

	h = singleton_hist();
	if ((keycode == KEY_ALT_R) || (keycode == KEY_DELETE))
	{
		if (!(line->btsearch))
		{
			line->btsearch = 1;
			btsearch_handle_signals();
			btsearch_init(line, h);
		}
		if (keycode == KEY_ALT_R)
			btsearch_next(line, h);
		else if (keycode == KEY_DELETE)
			btsearch_del(line, h);
		btsearch_refresh(line, h);
		return (1);
	}
	else if (line->btsearch && ft_isprint(keycode))
	{
		btsearch_add(keycode, line, h);
		btsearch_refresh(line, h);
		return (1);
	}
	else
	{
		line->btsearch = 0;
		btsearch_exit(line, h);
		edit_refresh(line);
	}
	return (0);
}
#endif
