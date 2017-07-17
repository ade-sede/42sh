/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btsearch_get_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 23:19:54 by vcombey           #+#    #+#             */
/*   Updated: 2017/06/08 23:20:16 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"
#include "history.h"

int		btsearch_get_input(t_line *line)
{
	unsigned long long	keycode;
	t_hist			*h;

//	c = singleton_btsearch();
	h = singleton_hist();
	btsearch_init(line, h);
	btsearch_refresh(line, h);
//	btsearch_set_signals();
	while (42)
	{
		keycode = 0;
		read(0, &keycode, 8);
		if (keycode == KEY_ALT_R) 
			btsearch_next(line, h);
		else if (keycode == KEY_DELETE) 
			btsearch_prev(line, h);
		else if (ft_isprint(keycode))
			btsearch_add(keycode, line, h);
		else if (keycode == KEY_ENTER || !ft_isprint(keycode))
		{
			btsearch_exit(line, h);
			return (1);
		}
		btsearch_refresh(line, h);
	}
	return (0);
}
