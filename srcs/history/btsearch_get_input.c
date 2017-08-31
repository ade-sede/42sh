#include "line_editing.h"
#include "history.h"

int		btsearch_get_input(t_line *line)
{
	unsigned long long	keycode;
	t_hist				*h;

	h = singleton_hist();
	btsearch_init(line, h);
	btsearch_refresh(line, h);
	btsearch_set_signals();
	while (42)
	{
		keycode = 0;
		read(0, &keycode, 8);
		if (h->signum == SIGINT)
			return (btsearch_handle_sigint(line, h));
		if (keycode == KEY_ALT_R)
			btsearch_next(line, h);
		else if (keycode == KEY_DELETE)
			btsearch_del(line, h);
		else if (ft_isprint(keycode))
			btsearch_add(keycode, line, h);
		else if (keycode == KEY_ENTER || !ft_isprint(keycode))
			return (btsearch_exit(line, h));
		btsearch_refresh(line, h);
	}
	return (0);
}
