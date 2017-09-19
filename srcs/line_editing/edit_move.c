/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:50 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:26 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

int		edit_word_left(t_line *line)
{
	if (line->pos > 0 && line->buff[line->pos] == '\0')
		edit_left(line);
	while (line->pos > 0 && line->buff[line->pos] == ' ')
		edit_left(line);
	while (line->pos > 0 && line->buff[line->pos] != ' ')
		edit_left(line);
	return (1);
}

int		edit_word_right(t_line *line)
{
	while (line->pos < line->len && line->buff[line->pos] == ' ')
		edit_right(line);
	while (line->pos < line->len && line->buff[line->pos] \
			&& line->buff[line->pos] != ' ')
		edit_right(line);
	return (1);
}

int		edit_home(t_line *line)
{
	put_ntermcap("le", line->pos);
	line->pos = 0;
	return (1);
}

int		edit_end(t_line *line)
{
	while (line->pos < line->len)
		edit_right(line);
	return (1);
}
