#include "line_editing.h"

static g_keycode[] =
{
	{KEY_LEFT, &edit_left},
	{KEY_RIGHT, &edit_right},
	{KEY_HOME, &edit_home},
	{KEY_END, &edit_end},
	{KEY_BACKSPACE, &edit_backspace},
//	{KEY_UP, &edit_up},
//	{KEY_DOWN, &edit_down},
	//{KEY_SHIFT_UP},
	//{KEY_SHIFT_DOWN},
	//{},
	//{},
	{NULL, NULL},
};

int		edit_loop(unsigned long long keycode, t_line *line)
{
	int	i;

	i = 0;
	while (g_keycode[i].key)
	{
		if (g_keycode[i].key == keycode)
			g_keycode[i].f(line);
		i++;
		else if (ft_isprint((char)keycode))
			edit_add(keycode, line);
	}
	return (1);
}
/*keycode == KEY_LEFT && line->pos > 0)
line->pos--;
else if (keycode == KEY_UP && line->hist != NULL)
	history_prev(line);
else if (keycode == KEY_DOWN && line->hist != NULL)
	history_next(line);
else if (keycode == KEY_RIGHT && line->pos < line->len)
	line->pos++;
else if (keycode == KEY_BACKSPACE && line->pos > 0)
	buff_del(line);
else if (keycode == KEY_HOME)
	line->pos = 0;
else if (keycode == KEY_END)
	line->pos = line->len;
else if (keycode == KEY_SHIFT_UP)
	line->pos = line->len;
else if (keycode == KEY_SHIFT_DOWN)
	line->pos = line->len;
else if (keycode == 18)
	istory_search(line);
else if (ft_isprint((char)keycode))
	buff_add(keycode, line);
	else
	printf("%lu", keycode);
	return (1);
	}
*/
char		*edit_get_input(t_env *env)
{
	unsigned long long	keycode;
	t_line		*s;

	line = line();
	while (42)
	{
		keycode = 0;
		read(0, &keycode, 8);
		if (keycode == KEY_ENTER)
		{
			ft_putchar('\n');
			return (line->buff);
		}
		else if (edit_loop(keycode, line))
			refresh_buff(0, env);
	}
}
