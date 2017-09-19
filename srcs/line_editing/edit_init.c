/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:50 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:25 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

t_line		*singleton_line(void)
{
	static t_line	s;

	return (&s);
}

void		edit_line_init(t_line *line)
{
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
	line->len = 0;
}
