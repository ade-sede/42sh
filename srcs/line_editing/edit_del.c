/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_del.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 22:41:02 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/15 22:41:13 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

int	edit_backspace(t_line *line)
{
	size_t	s;

	if (line->pos == 0)
		return (0);
	ft_memmove((void*)(line->buff + line->pos - 1), \
			(void*)(line->buff + line->pos), line->len - line->pos);
	line->buff[line->len - 1] = '\0';
	line->pos--;
	line->len--;
	put_termcap("le");
	s = ft_strlen(line->buff + line->pos);
	write(1, line->buff + line->pos, s);
	ft_putchar_fd(' ', 2);
	put_ntermcap("le", s + 1);
	if ((((line->prompt_len + ft_strlen(line->buff))) % line->ws_col) == \
			line->ws_col - 1)
		put_termcap("nd");
	return (1);
}
