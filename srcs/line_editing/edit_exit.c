/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 05:07:29 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 05:08:42 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"
#include "history.h"

char	*edit_exit(t_line *line)
{
	move_cursor_lastline(line);
	move_cursor_bufflen_from_lastline(line);
	ft_putchar('\n');
	return (line->buff);
}
