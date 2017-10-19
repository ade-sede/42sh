/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:40:48 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/19 13:40:56 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <unistd.h>
#include "env.h"
#include "exec.h"
#include "builtin.h"
#include "history.h"
#include "line_editing.h"
#include "lexer.h"
#include "parser.h"

/*
**	Receives an array containing the command name and its arguments, forwards
**	this array to the appropriate function then frees it.
*/

void	exec(t_env *env, const char **argv, t_lst_head *head)
{
	size_t		index;

	index = 0;
	if (*argv != NULL)
	{
		if (!(exec_builtin(env, argv, head)))
			fork_exec_bin(env, argv, head);
	}
	else
		env->previous_exit = EXIT_FAILURE;
	while (argv[index] != NULL)
	{
		free((void*)(argv[index]));
		index++;
	}
	free(argv);
}

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

char	*line_editing_get_input(t_line *line, t_hist *hist,
		void (*sig_handler)(void))
{
	put_prompt(line);
	history_init(hist);
	edit_line_init(line, sig_handler);
	return (edit_get_input());
}

void	main_loop(t_env *env)
{
	char		*buff;

	init_main_loop(singleton_line(), singleton_hist());
	while (42)
	{
		load_prompt(env, singleton_line(), "PS1", "$> ");
		buff = ft_strdup(line_editing_get_input(singleton_line(), \
					singleton_hist(), &edit_set_signals_open));
		if (!ft_str_is_clr(buff))
			lex_and_parse(NULL, NULL, buff);
		free(buff);
	}
}
