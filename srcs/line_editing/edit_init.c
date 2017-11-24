/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:37 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:33 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

/*
**	Setting up singleton to be accessible from any scope.
*/

t_line		*singleton_line(void)
{
	static t_line	s;

	return (&s);
}

/*
**	Safe init of all variables in the t_line.
*/

int			g_abort_opening;

void		edit_line_init(t_line *line, void (*sig_handler)(void))
{
	g_abort_opening = 0;
	ft_bzero(line->buff, line->len);
	if (line->size >= BUFF_LINE_SIZE)
	{
		free(line->buff);
		line->buff = ft_strnew(BUFF_LINE_SIZE);
		line->size = BUFF_LINE_SIZE;
	}
	line->verbatim = 0;
	line->completion = 0;
	line->btsearch = 0;
	line->history = 0;
	line->visu_mode = 0;
	line->pos = 0;
	line->old_pos = 0;
	line->len = 0;
	line->sig_handler = sig_handler;
}
