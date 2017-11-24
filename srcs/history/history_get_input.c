/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_get_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:36 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:20 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

int		history_get_input(t_line *line, unsigned long keycode)
{
	t_hist			*h;

	h = singleton_hist();
	if (keycode == KEY_UP || keycode == KEY_DOWN)
	{
		if (!(line->history))
		{
			history_move_init(line, h);
			line->history = 1;
		}
		if (keycode == KEY_UP)
			history_next(line, h);
		else if (keycode == KEY_DOWN)
			history_prev(line, h);
		return (1);
	}
	else if (line->history)
	{
		line->history = 0;
		history_move_exit(line, h);
		return (0);
	}
	return (0);
}
