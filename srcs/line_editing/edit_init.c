/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:40:47 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/11 22:40:58 by vcombey          ###   ########.fr       */
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
	if (line->size > BUFF_LINE_SIZE)
	{
		free(line->buff);
		line->buff = ft_strnew(BUFF_LINE_SIZE);
		line->size = BUFF_LINE_SIZE;
	}
	line->completion = 0;
	line->btsearch = 0;
	line->history = 0;
	line->visu_mode = 0;
	line->pos = 0;
	line->old_pos = 0;
	line->len = 0;
	line->sig_handler = sig_handler;
}
