/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comple_get_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:13:51 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "failure.h"
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

/*
**	Returns yes if we are allowed to go in comple_get_input
**	Returns no if we are not (meaning we wanna go in edit_add)
**
**	Edit_add case
**	- keycode is tab, and there is nothing between
**				the start of the line and line->pos.
**	- keycode is tab, and there is nothing between
**				the start of the preceding newline and me.
**	-
*/

static	int		valid_comple(t_line *line, int keycode)
{
	char		tmp;
	char		*start_ptr;

	if (!(line->completion) && keycode == KEY_TAB)
	{
		tmp = line->buff[line->pos];
		line->buff[line->pos] = 0;
		start_ptr = ft_strrchr(line->buff, '\n');
		line->buff[line->pos] = tmp;
		if (!start_ptr)
			start_ptr = line->buff;
		if (ft_str_is_clear_n(start_ptr, line->buff + line->pos - start_ptr))
			return (FALSE);
		else if (line->verbatim)
		{
			line->verbatim = 0;
			return (FALSE);
		}
		return (TRUE);
	}
	return (FALSE);
}

int				comple_loop(unsigned long long keycode, t_line *line,
		t_comple *c)
{
	int			i;

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

int				comple_get_input(t_line *line, int keycode)
{
	t_comple	*c;

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
	if (valid_comple(line, keycode))
	{
		comple_set_signals();
		if (!(comple_init(line, c)))
			return (1);
		comple_refresh(line, *c);
		line->completion = 1;
		return (1);
	}
	return (0);
}
