/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:37 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:31 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "failure.h"
#include "color.h"

void	realoc_line_buff(t_line *line, size_t new_size)
{
	line->buff = cl_realloc(line->size, line->buff, new_size);
	line->size = new_size;
}

void	edit_add(int keycode, t_line *line)
{
	if (line->len == line->size - 1)
		realoc_line_buff(line, line->size + BUFF_LINE_SIZE);
	ft_memmove((void*)(line->buff + line->pos + 1), \
			(void*)(line->buff + line->pos), line->len - line->pos);
	line->buff[line->pos] = (char)keycode;
	line->pos++;
	line->len++;
	edit_refresh(line);
}
