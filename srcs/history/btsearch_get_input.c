#include "line_editing.h"
#include "history.h"

int		btsearch_init(t_line *line, t_hist *h)
{
	ft_strclr(line->buff);
	line->len = 0;
	line->pos = 0;
	(void)h;
	return (1);
}

int		btsearch_get_input(t_line *line)
{
	unsigned long long	keycode;
	t_hist			*h;

//	c = singleton_btsearch();
	h = singleton_hist();
	btsearch_init(line, h);
	btsearch_refresh(line, h);
//	btsearch_set_signals();
	while (42)
	{
		keycode = 0;
		read(0, &keycode, 8);
		if (keycode == KEY_ENTER || !ft_isprint(keycode))
		{
			btsearch_exit(line, h);
			return (1);
		}
		btsearch_add(keycode, line, h);
		btsearch_refresh(line, h);
	}
	return (0);
}
