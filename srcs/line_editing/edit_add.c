/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 23:19:54 by vcombey           #+#    #+#             */
/*   Updated: 2017/07/19 10:26:30 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

void	edit_add(int keycode, t_line *line)
{
	if (line->pos == line->len)
		line->buff[line->len] = (char)keycode;
	else
	{
		ft_memmove((void*)(line->buff + line->pos + 1), \
				(void*)(line->buff + line->pos), line->len - line->pos);
		line->buff[line->pos] = (char)keycode;
	}
	line->pos++;
	line->len++;
}
