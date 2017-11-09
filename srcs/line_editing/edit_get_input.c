#include "line_editing.h"
#include "completion.h"
#include "history.h"
#include "failure.h"

static t_edit_func	g_edit_func[] =
{
	{KEY_LEFT, &edit_left},
	{KEY_RIGHT, &edit_right},
	{KEY_ALT_RIGHT, &edit_word_right},
	{KEY_ALT_LEFT, &edit_word_left},
	{KEY_ALT_UP, &edit_up},
	{KEY_ALT_DOWN, &edit_down},
	{KEY_HOME, &edit_home},
	{KEY_END, &edit_end},
	{KEY_BACKSPACE, &edit_backspace},
	{KEY_ALT_C, &copy},
	{KEY_ALT_V, &enter_visual_mode},
	{KEY_ALT_P, &paste},
	{KEY_CTRL_D, &control_d},
	{KEY_DELETE, &edit_del},
	{KEY_CTRL_L, &control_l},
	{0, NULL}
};

/*
 **	Calls the routine corresponding to the keycode. If the keycode doesnt
 **	correspond to a command, it is simply appended to the buffer. (and will be
 **	printed next time a refresh is called).
 */

int					edit_loop(unsigned long long keycode, t_line *line)
{
	int	i;

	i = 0;
	while (g_edit_func[i].keycode)
	{
		if (g_edit_func[i].keycode == keycode)
		{
			keycode = g_edit_func[i].f(line);
		}
		i++;
	}
	if (ft_isprint((char)keycode))
		edit_add(keycode, line);
	return (1);
}

/*
 **	The function which starts the line editing, sets up the signals. Receives
 **	the keycode from history_move_loop(). Enters a loop in which each keycode
 **	is sent to edit_loop(), where it will be treated. If keycode is KEY_ENTER,
 **	editing is complete, and the line is returned. Every time is key is
 **	pressed, the displayed line is refreshed.
 */

static void			init_read(t_line *l, unsigned long *keycode)
{
	*keycode = 0;
	l->old_pos = l->pos;
}

int	g_abort_opening;

char				*edit_get_input(void)
{
	unsigned long	keycode;
	t_line			*l;

	l = singleton_line();
	l->sig_handler();
	while (42)
	{
		init_read(l, &keycode);
		read(0, &keycode, 1);
#ifdef DEBUG_TAB
		t_coor	pos;
		ssize_t	i;
		i = ft_strichr(l->buff, '\'');
		if (i != -1)
		{
			pos = get_char_visual_coor(l, i);
			//logwrite("/Users/seddaoud/projects/42sh/log/def", __func__, "{%d ; %d}\n", pos.x, pos.y);
		}
#endif
		if (g_abort_opening)
			return (edit_exit(l));
		if (keycode == KEY_CTRL_D && l->heredoc && l->len == 0)
			return (control_d_heredoc(l));
		if (keycode == 27 || keycode > 127)
			read(0, (char *)&keycode + 1, 7);
		if (keycode != KEY_ALT_UP && keycode != KEY_ALT_DOWN)
			l->col_target = -1;
		if (btsearch_get_input(l, keycode) || comple_get_input(l, keycode) ||
				history_get_input(l, keycode))
			continue ;
		if (keycode == KEY_ENTER || (char)keycode == (l->read).delim)
		{
			if (keycode == KEY_ENTER && KEY_ENTER != (l->read).delim)
				edit_add(keycode, l);
			else
				return (edit_exit(l));
		}
		edit_loop(keycode, l);
		if (l->read.nchars && l->read.nchars == (int)l->len) 
			return (edit_exit(l));
	}
	return (NULL);
}
