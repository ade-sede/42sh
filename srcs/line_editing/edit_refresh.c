/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_refresh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:37 by ade-sede          #+#    #+#             */
/*   Updated: 2017/12/18 18:30:37 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_coloring.h"
#include "t_env.h"
#include "t_lexer.h"
#include <stdio.h>
#include "failure.h"
#include "color.h"
#include "shopt.h"

void			edit_refresh_cursor(t_line *line)
{
	cursor_goto_buff(line, line->pos, line->len);
}

/*
** Refresh line write buff on multiple lines per ws_col.  If the cursor is in
** the last colomn, move it to the next line.
*/

static void		handle_newline(t_line *line, int ret)
{
	t_coor	pos;

	pos = get_char_visual_coor(line, line->len);
	if (pos.x != 0)
		return ;
	if (ret != DEFAULT)
		return ;
	if (line->buff[line->len] == '\n' || line->buff[line->pos] == '\n')
		return ;
	if (line->buff[line->len - 1] == '\n')
		return ;
	if (line->buff[line->len] == '\t' || line->buff[line->pos] == '\t')
		return ;
	if (line->buff[line->len - 1] == '\t')
		return ;
	put_termcap("do");
}

void			edit_refresh_line(t_line *line)
{
	t_lexer lex;
	int		ret;

	ret = DEFAULT;
	if (singleton_env()->option & SYNCOLOR)
	{
		init_lexer(&lex, line->buff);
		ret = loop_le_delim(&lex, line);
		if (ret != DEFAULT)
		{
			ft_putstr_fd(RED, 2);
			ft_putchar_fd('_', 2);
			ft_putstr_fd(RESET, 2);
		}
		free_lexer(&lex);
	}
	else
		term_putstr(line);
	handle_newline(line, ret);
}

void			edit_refresh_clear(t_line *line)
{
	int		y;

	cursor_goto_buff(line, 0, line->old_pos);
	y = get_prompt_visual_offset(line).y;
	put_ntermcap("up", (size_t)y);
	put_termcap("cr");
	put_termcap("cd");
}

void			edit_refresh(t_line *line)
{
	edit_refresh_clear(line);
	put_prompt(line);
	edit_refresh_line(line);
	edit_refresh_cursor(line);
}
