#include "completion.h"
#include "line_editing.h"

static t_comple_func	g_comple_func[] =
{
	{KEY_LEFT, &comple_left},
	{KEY_RIGHT, &comple_right},
	{KEY_UP, &comple_up},
	{KEY_DOWN, &comple_down},
	{KEY_TAB, &comple_down},
	{0, NULL}
};

int		comple_loop(unsigned long long keycode, t_line *line,
		t_comple *c)
{
	int	i;

	i = 0;
	while (g_comple_func[i].keycode)
	{
		if (g_comple_func[i].keycode == keycode)
		{
			g_comple_func[i].f(c);
			return (1);
		}
		i++;
	}
	return (0);
	(void)line;
}

int		comple_get_input(t_line *line, int keycode)
{
	t_comple			*c;
	//add by seddoaud
	char	tmp;
	//end add

	c = singleton_comple();
	if (line->completion)
	{
		if (keycode == KEY_ENTER || (!comple_loop(keycode, line, c)))
		{
			line->completion = 0;
			comple_exit_matched(line, *c, keycode);
			return (keycode == KEY_ENTER ? 1 : 0);
		}
		comple_refresh(line, *c);
		return (1);
	}
	if (!(line->completion) && keycode == KEY_TAB)
	{
		tmp = line->buff[line->pos];
		line->buff[line->pos] = '\0';
		if (ft_str_is_clr(line->buff))
		{
			line->buff[line->pos] = tmp;
			edit_add('\t', line);
			put_termcap("ta");

		}
		line->buff[line->pos] = tmp;
		comple_set_signals();
		if (!(comple_init(line, c)))
			return (0);
		comple_refresh(line, *c);
		line->completion = 1;
		return (1);
	}
	return (0);
}
