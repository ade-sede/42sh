/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 23:19:54 by vcombey           #+#    #+#             */
/*   Updated: 2017/07/22 19:06:23 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

void	realoc_line_buff(char **buff, unsigned int *size, unsigned int size_needed)
{
    char	*new;
    unsigned int	new_size;

    new_size = size_needed + LINE_BUFF_SIZE;
    new = ft_strnew(new_size);
    ft_strcpy(new, *buff);
    free(*buff);
    *buff = new;
    *size = new_size;
}

void	edit_add(int keycode, t_line *line)
{
    if (line->pos == line->len)
	line->buff[line->len] = (char)keycode;
    else
    {
	if (line->len + 1 >= line->size)
	    realoc_line_buff(&line->buff, &line->size, line->len + 1);
	ft_memmove((void*)(line->buff + line->pos + 1), \
		(void*)(line->buff + line->pos), line->len - line->pos);
	line->buff[line->pos] = (char)keycode;
    }
    line->pos++;
    line->len++;
}
