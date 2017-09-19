/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:50 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:24 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

int		control_d(t_line *line)
{
	if (line->len != 0)
		return (1);
	if (line->heredoc == 1 && line->len != 0)
		return (1);
	(void)line;
	ft_putchar('\n');
	exit(0);
}

char	*control_d_heredoc(t_line *line)
{
	edit_add(4, line);
	return (edit_exit(line));
}
