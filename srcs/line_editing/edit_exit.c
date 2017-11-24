/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:37 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:32 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

/*
**	Exit routine.
**	Moves cursor to the end of the input, insert a newline to the end of
**	the buffer Returns the address of the buffer.
*/

char	*edit_exit(t_line *line)
{
	move_cursor_lastline(line);
	move_cursor_bufflen_from_lastline(line);
	edit_insert_str(line, line->buff + ft_strlen(line->buff), "\n");
	ft_putchar_fd('\n', 2);
	return (line->buff);
}
