#include "line_editing.h"
#include "history.h"

int		btsearch_special_keys(t_line *line, t_hist *h, unsigned long keycode)
{
	if (keycode == KEY_ALT_R && !(line->btsearch))
	{
		line->btsearch = 1;
		btsearch_handle_signals();
		btsearch_init(line, h);
	}
	if (keycode == KEY_ALT_R)
		btsearch_next(line, h);
	else if (keycode == KEY_BACKSPACE)
		btsearch_del(line, h);
	btsearch_refresh(line, h);
	return (1);
}

int		btsearch_get_input(t_line *line, unsigned long keycode)
{
	t_hist				*h;

	h = singleton_hist();
	if (!(line->btsearch) && (keycode == KEY_BACKSPACE))
		return (0);
	if ((keycode == KEY_ALT_R) || (keycode == KEY_BACKSPACE))
		return (btsearch_special_keys(line, h, keycode));
	else if (line->btsearch && ft_isprint(keycode))
	{
		btsearch_add(keycode, line, h);
		btsearch_refresh(line, h);
		return (1);
	}
	else if (line->btsearch)
	{
		edit_set_signals();
		line->btsearch = 0;
		btsearch_exit(line, h);
		edit_refresh(line);
	}
	return (0);
}
