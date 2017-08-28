/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_move_loop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 05:07:29 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/28 18:03:45 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include "line_editing.h"

/*
**	Reads from standard input. If the pressed key is related to history
**	browsing, triggers the coresponding routine and refreshes the display.
**	Otherwise returns the keycode (to edit_get_input()).
*/

void	history_move_loop(t_line *line, unsigned long keycode, int *history)
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
	}
	else if (*history)
	{
		*history = 0;
		history_move_exit(line, h);
	}
}
