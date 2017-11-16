#include <stdio.h>
#include "environ.h"
#include <fcntl.h>
#include <stdlib.h>
#include "libft.h"
#include "exec.h"
#include "local.h"
#include <pwd.h>
#include "modes.h"
#include "get_next_line.h"

char	*line_editing_get_line(t_line *line, t_hist *hist,
		void (*sig_handler)(void))
{
	put_prompt(line);
	history_init(hist);
	edit_line_init(line, sig_handler);
	return (edit_get_input());
}

char	*stream_get_line(int stream)
{
	char	*buff;
	buff = NULL;
	get_next_line(stream, &buff);
	return (buff);
}

char	*string_get_line(char *string)
{
	char	*res = NULL;
	int		i = 0;

	while (string[i])
	{
		if (string[i] == '\n')
			break;
		i++;
	}
	if (i > 0)
	{
		res = ft_strndup(string, i);
		string += i;
	}
	return (res);
}

int		get_input(t_modes *modes, char **buff)
{
	if (modes->mode == INTERACTIVE_MODE)
		*buff = ft_strdup(line_editing_get_line(singleton_line(), \
					singleton_hist(), &edit_set_signals_open));
	else if (modes->mode == STRING_MODE)
		*buff = string_get_line(modes->string);
	else
		*buff = stream_get_line(modes->stream);
	if (!*buff)
		return (0);
	return (1);
}

int		reopen(t_lexer *lex, t_parser *parser, t_modes *modes)
{
	char	*new_command;

	if (modes->mode == INTERACTIVE_MODE)
		reopen_line_editing(lex, parser, &new_command);
	else if (!get_input(modes, &new_command))
		return (0);
	lex->line = ft_strjoin_free(lex->line, new_command, 0b10);
	return (1);
}

