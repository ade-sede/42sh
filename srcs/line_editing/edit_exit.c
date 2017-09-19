/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:50 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:25 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"
#include "history.h"

char	*edit_exit(t_line *line)
{
	move_cursor_lastline(line);
	move_cursor_bufflen_from_lastline(line);
	ft_putchar_fd('\n', 2);
	return (line->buff);
}
