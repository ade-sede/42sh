/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_move_arrows.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:40:47 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/11 22:40:58 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"
#include "failure.h"

/*
** static ssize_t	newline_on_the_left(t_line *line) {
** 	char	old_char;
** 	ssize_t	newl;
** 	size_t	i;
**
** 	i = 0;
** 	old_char = line->buff[line->pos];
** 	line->buff[line->pos] = 0;
** 	newl = ft_strrichr(line->buff, '\n');
** 	line->buff[line->pos] = old_char;
** 	while (newl + i != line->pos)
** 		++i;
** 	if (i >= line->ws_col)
** 		newl = -1;
** 	return (newl);
** }
*/

int		edit_up(t_line *line)
{
	size_t	new_pos;
	t_coor	pos;

	pos = get_char_visual_coor(line, line->pos);
	if (line->col_target == -1)
		line->col_target = pos.x;
	new_pos = get_char_mem_coor_relative(line, line->col_target - pos.x, -1);
	line->pos = cursor_goto_buff(line, new_pos, line->pos);
	if (line->visu_mode)
	{
		line->old_pos = line->pos;
		edit_refresh(line);
	}
	return (0);
}

int		edit_down(t_line *line)
{
	size_t	new_pos;
	t_coor	pos;

	pos = get_char_visual_coor(line, line->pos);
	if (line->col_target == -1)
		line->col_target = pos.x;
	new_pos = get_char_mem_coor_relative(line, line->col_target - pos.x, 1);
	line->pos = cursor_goto_buff(line, new_pos, line->pos);
	if (line->visu_mode)
	{
		line->old_pos = line->pos;
		edit_refresh(line);
	}
	return (0);
}

int		edit_left(t_line *line)
{
	if (line->pos == 0)
		return (0);
	line->pos = cursor_goto_buff(line, line->pos - 1, line->pos);
	if (line->visu_mode)
	{
		line->old_pos = line->pos;
		edit_refresh(line);
	}
	return (1);
}

int		edit_right(t_line *line)
{
	if (line->pos >= line->len)
		return (0);
	line->pos = cursor_goto_buff(line, line->pos + 1, line->pos);
	if (line->visu_mode)
	{
		line->old_pos = line->pos;
		edit_refresh(line);
	}
	return (1);
}
