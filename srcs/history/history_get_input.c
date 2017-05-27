#include "history.h"
#include "line_editing.h"

static t_hist_func	g_hist_func[] =
{
	{KEY_UP, &history_next},
	{KEY_DOWN, &history_prev},
	{0, NULL}
};

int		history_loop(unsigned long long keycode, t_line *line, t_hist *h)
{
	int	i;

	i = 0;
	while (g_hist_func[i].keycode)
	{
		if (g_hist_func[i].keycode == keycode)
		{
			g_hist_func[i].f(line, h);
			return (1);
		}
		i++;
	}
	return (0);
}

unsigned long	history_get_input(t_line *line)
{
	unsigned long	keycode;
	t_hist		*h;

	h = singleton_hist();
	history_init(line, h);
	while (42)
	{
		keycode = 0;
		read(0, &keycode, 8);
		if (!(hist_loop(keycode, line, h)))
			return (keycode);
		edit_refresh(line);
	}
}
