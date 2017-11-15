#include "libft.h"
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

char	*line_editing_get_input(t_line *line, t_hist *hist,
		void (*sig_handler)(void))
{
	put_prompt(line);
	history_init(hist);
	edit_line_init(line, sig_handler);
	return (edit_get_input());
}

int		stream_get_line(int stream, char **buff)
{
	*buff = NULL;
	if (get_next_line(stream, buff) <= 0)
		return (0);
	return (1);
}

void	main_loop(t_env *env, int stream, char *buff_c_opt, int c_opt)
{
	char		*buff;

	init_main_loop(singleton_line(), singleton_hist());
	while (42)
	{
		do_job_notification(singleton_jc());
		load_prompt(env, singleton_line(), "PS1", "$> ");
		if (singleton_jc()->shell_is_interactive)
			buff = ft_strdup(line_editing_get_input(singleton_line(), \
						singleton_hist(), &edit_set_signals_open));
		else if (c_opt)
			buff = ft_strdup(buff_c_opt);
		else if (!(stream_get_line(stream, &buff)))
			exit(ft_atoi(local_get_value(env->local, "$?")));
		if (!ft_strequ(buff, "\n"))
			lex_and_parse(NULL, buff, stream);
		free(buff);
		if (c_opt)
			exit(ft_atoi(local_get_value(env->local, "$?")));
	}
}
