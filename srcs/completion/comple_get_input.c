/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comple_get_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 05:07:29 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/28 18:48:54 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"
#include "line_editing.h"
#include <stdio.h>

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

int		comple_get_input(t_line *line, int keycode, int *completion)
{
	t_comple			*c;

	c = singleton_comple();
	if (*completion)
	{
		if (keycode == KEY_ENTER)
		{
			*completion = 0;
			comple_exit_matched(line, *c, keycode);
			return (1);
		}
		else if (!comple_loop(keycode, line, c))
		{
			*completion = 0;
			comple_exit_matched(line, *c, keycode);
			return (0);
		}
		comple_refresh(line, *c);
		return (1);
	}
	if (!(*completion) && keycode == KEY_TAB)
	{
		if (!(comple_init(line, c)))
			return (0);
		comple_refresh(line, *c);
		//comple_set_signals();
		*completion = 1;
		return (1);
	}
	return (0);
}
