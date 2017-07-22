/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 23:19:54 by vcombey           #+#    #+#             */
/*   Updated: 2017/07/22 22:09:22 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"
#include <stdio.h>

void	realoc_line_buff(char **buff, unsigned int *size, unsigned int size_needed)
{
    char	*new;
    unsigned int	new_size;

    new_size = (size_needed / BUFF_LINE_SIZE + 2) * BUFF_LINE_SIZE;
    /*
**	    printf("\n, %d,\n %d,\n, %d",singleton_line()->size, singleton_line()->len, size_needed);
**	    printf("\nrealloc\n");
*/
    new = ft_strnew(new_size);
    ft_strcpy(new, *buff);
    free(*buff);
    *buff = new;
    *size = new_size;
//    printf("\n new size %d\n", *size);
}

void	edit_add(int keycode, t_line *line)
{
    //printf("\n, %d,\n %d,\n",line->size, line->len);
	if (line->len >= line->size)
	    realoc_line_buff(&line->buff, &line->size, line->len + 1);
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
