/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 05:07:29 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 05:08:45 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

int		edit_word_left(t_line *line)
{
	if (line->pos > 0 && line->buff[line->pos] == '\0')
		line->pos--;
	while (line->pos > 0 && line->buff[line->pos] == ' ')
		line->pos--;
	while (line->pos > 0 && line->buff[line->pos] != ' ')
		line->pos--;
	return (1);
}

int		edit_word_right(t_line *line)
{
	while (line->pos < line->len && line->buff[line->pos] == ' ')
		line->pos++;
	while (line->pos < line->len && line->buff[line->pos] \
			&& line->buff[line->pos] != ' ')
		line->pos++;
	return (1);
}

int		edit_home(t_line *line)
{
	line->pos = 0;
	return (1);
}

int		edit_end(t_line *line)
{
	line->pos = line->len;
	return (1);
}
