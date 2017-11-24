/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:05 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include "t_env.h"
#include "environ.h"
#include "exec.h"
#include "builtin.h"
#include "history.h"
#include "line_editing.h"
#include "lexer.h"
#include "get_next_line.h"
#include "parser.h"
#include "local.h"
#include <stdio.h>
#define LOCAL_BUFF_SIZE 4096

void	init_main_loop(t_line *line, t_hist *hist)
{
	(void)hist;
	line->len = 0;
	line->pos = 0;
	line->visu_mode = 0;
	line->copied_text = NULL;
	line->ws_col = get_ws_col();
	line->buff = ft_strnew(BUFF_LINE_SIZE);
	env_add_change(singleton_env(), "PS1", "$> ");
	env_add_change(singleton_env(), "PS2", "dquote> ");
	env_add_change(singleton_env(), "PS3", "quote> ");
	line->size = BUFF_LINE_SIZE;
	load_prompt(singleton_env(), line, "PS1", "$> ");
	line->heredoc = 0;
	line->col_target = -1;
}

int		main_loop(t_env *env, t_modes *modes)
{
	char		*buff;

	if (modes->mode == INTERACTIVE_MODE)
		init_main_loop(singleton_line(), singleton_hist());
	while (42)
	{
		if (modes->mode == INTERACTIVE_MODE)
		{
			do_job_notification(singleton_jc());
			load_prompt(env, singleton_line(), "PS1", "$> ");
		}
		if (!get_input(modes, &buff))
			return (0);
		if (!lex_and_parse(NULL, buff, modes))
			return (0);
		free(buff);
	}
}
