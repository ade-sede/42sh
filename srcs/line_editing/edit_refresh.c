/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_refresh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:37 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:34 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_coloring.h"
#include "t_env.h"
#include "t_lexer.h"
#include <stdio.h>
#include "failure.h"
#include "color.h"
#include "shopt.h"

void	edit_refresh_cursor(t_line *line)
{
	cursor_goto_buff(line, line->pos, line->len);
}

/*
** Refresh line write buff on multiple lines per ws_col.  If the cursor is in
** the last colomn, move it to the next line.
*/

void	edit_refresh_line(t_line *line)
{
	t_coor	pos;
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
	pos = get_char_visual_coor(line, line->len);
	if (pos.x == 0 && (line->pos != 0 && line->buff[line->pos - 1] != '\n' \
				&& line->buff[line->pos - 1] != '\t') && ret == DEFAULT)
		put_termcap("do");
}

void	edit_refresh_clear(t_line *line)
{
	int		y;

	cursor_goto_buff(line, 0, line->old_pos);
	y = get_prompt_visual_offset(line).y;
	put_ntermcap("up", (size_t)y);
	put_termcap("cr");
	put_termcap("cd");
}

void	edit_refresh(t_line *line)
{
	edit_refresh_clear(line);
	put_prompt(line);
	edit_refresh_line(line);
	edit_refresh_cursor(line);
}
