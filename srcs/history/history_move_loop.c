/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_move_loop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 05:07:29 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/28 19:01:18 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include "line_editing.h"

int		history_get_input(t_line *line, unsigned long keycode, int *history)
{
	t_hist			*h;

	h = singleton_hist();
	if (keycode == KEY_UP || keycode == KEY_DOWN)
	{
		if (!(*history))
		{
			history_move_init(line, h);
			*history = 1;
		}
		if (keycode == KEY_UP)
			history_next(line, h);
		else if (keycode == KEY_DOWN)
			history_prev(line, h);
		edit_refresh(line);
		return (1);
	}
	else if (*history)
	{
		*history = 0;
		history_move_exit(line, h);
		return (0);
	}
	return (0);
}
