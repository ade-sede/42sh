/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comple_refresh.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 23:19:54 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/25 23:39:36 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"
#include "line_editing.h"
#include <stdio.h>

void	ft_putstr_padding_space(char *str, unsigned int size)
{
	unsigned int len;

	len = ft_strlen_color(str);
	ft_putstr(str);
	while ((size - len) > 0)
	{
		write(1, " ", 1);
		size--;
	}
}

void	comple_refresh_elem(t_comple c, int indice)
{
	if (indice == c.pos)
		ft_putstr("\e[;30;47m");
	ft_putstr_padding_space(c.matches[indice], c.max_len);
	put_termcap("me");
	write(1, "  ", 2);
}

void	comple_line_refresh(t_line *line, t_comple c)
{
(void)line;
(void)c;
	/*
	size_t	n;

	put_termcap("cr");
	put_termcap("dl");
	put_prompt(NULL);
	ft_putnstr(line->buff, line->pos);
	if (c.pos != -1)
		ft_putstr(c.matches[c.pos]);
	ft_putstr(line->buff + line->pos);
	n = line->len - line->pos;
	if (c.pos != -1)
		n += ft_strlen(c.matches[c.pos]);
	put_ntermcap("le", n);

*/
}


int	comple_refresh(t_line *line, t_comple c)
{
	size_t	co;
	size_t	li;
	size_t	li_start;

	put_termcap("cd");	
	li_start = 0;
	if (c.nb_lines > c.ws_row)
	{
		if (c.pos == -1)
			li_start = 0;
		else
			li_start = (c.pos % c.nb_lines / (c.ws_row - 1)) * (c.ws_row - 1);
	}
	move_cursor_lastline(line);
	//comple_clear(c);
	li = li_start;
	while (li < c.nb_lines && li - li_start < c.ws_row - 1)
	{
		co = 0;
		put_termcap("do");
		put_termcap("cr");
		while (co < c.nb_colones && co * c.nb_lines + li < c.nb_matches)
		{
			//goto_termcap("ch", co, 0);
			comple_refresh_elem(c, co * c.nb_lines + li);
			co++;
		}
		li++;
	}
	put_ntermcap("up", c.nb_lines);
	move_cursor_firstline_from_lastline(line);
	put_prompt(line);
	line->visu_mode ? edit_refresh_visu(line) : edit_refresh_line(line);
	edit_refresh_cursor(line);
	//comple_line_refresh(line, c);
	return (1);
}
