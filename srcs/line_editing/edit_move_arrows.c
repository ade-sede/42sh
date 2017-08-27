/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_move_arrows.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 05:07:29 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 05:08:46 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

int		edit_up(t_line *line)
{
	if (line->pos >= line->ws_col)
		line->pos -= line->ws_col;
	return (1);
}

int		edit_down(t_line *line)
{
	if (line->pos + line->ws_col <= line->len)
		line->pos += line->ws_col;
	return (1);
}

int		edit_left(t_line *line)
{
	if (line->pos > 0)
		line->pos--;
	return (1);
}

int		edit_right(t_line *line)
{
	if (line->pos < line->len)
		line->pos++;
	return (1);
}
