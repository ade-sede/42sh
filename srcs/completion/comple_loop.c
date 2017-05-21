#include "completion.h"
#include "line_editin.h"

static t_comple_func	g_comple_func[] =
{
	{KEY_LEFT, &comple_left},
	{KEY_RIGHT, &comple_right},
	{KEY_UP, &comple_up},
	{KEY_DOWN, &comple_down},
	{KEY_TAB, &comple_down},
	{0, NULL}
};

int		comple_loop(unsigned long long keycode, t_line *line, t_comple *c)
{
	int	i;

	i = 0;
	while (g_comple_func[i].keycode)
	{
		if (g_comple_func[i].keycode == keycode)
		{
			g_comple_func[i].f(line, comple);
			return (1);
		}
		i++;
	}
	return (0);
}

int		comple_get_input(t_line *line)
{
	unsigned long long	keycode;
	t_comple		c;

	if (!(comple_init(line, &c)))
		return (0);
	while (42)
	{
		keycode = 0;
		read(0, &keycode, 8);
		if (keycode == KEY_ENTER)
		{
			comple_exit_matched(line, c);
			return (1);
		}
		else if (!(comple_loop(keycode, l, &c)))
		{
			comple_free(c);
			return (1);
		}
		comple_refresh(0, env);
	}
	return (1);
}
