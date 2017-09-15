#include "lexer.h"
#include "libft.h"
#include "exec.h"
#include <stdio.h>
#include "line_editing.h"
#include "history.h"
#include "color.h"

/*
**	Determines if the char we are reading should or not be included in the
**	token.
**	If not, it closes the last token by returning the index of its last char,
**	and putting lex->index on the first char of the next potential token.
*/


void	append_history(char *command)
{
	t_hist	*h;
	t_list_d	*list;
	char	*full_command;

	h = singleton_hist();
	list = h->list->first;

	command[ft_strlen(command) - 1] = 0;
	full_command = ft_strjoin(list->data, command);
	list->data = ft_strchange(list->data, full_command);
}

void		reopen_line_editing(t_lexer *lex)
{
#ifndef NO_TERMCAPS
	char	*new_command;
#else
	char	new_command[4096];
#endif

#ifndef NO_TERMCAPS
	if (lex->state == '"')
		load_prompt(singleton_env(), singleton_line(), "PS2", "dquote> ");
	if (lex->state == '\'')
		load_prompt(singleton_env(), singleton_line(), "PS3", "dquote> ");
#endif
#ifndef NO_TERMCAPS
	new_command = ft_strdup(line_editing_get_input(singleton_env(), singleton_line(), \
			singleton_hist()));
	new_command = ft_strchange(new_command, ft_strjoin(new_command, "\n"));
	dprintf(2, MAG"#"CYN"%s"MAG"#\n"RESET, new_command);//			REMOVE		
#else
	bzero(new_command, 4096);
	read(0, new_command, 4096);
#endif
	lex->line = ft_strchange((char*)lex->line, ft_strjoin((char*)lex->line, new_command));
	append_history(new_command);	// This line removes the \n, everything gets fucked up
	free(new_command);
}

static int	match_part_1(t_lexer *lex, size_t token_start)
{
	int		ret;

	ret = -1;
	if (IS_INPUT_END(lex->line[lex->index]) && !(IS_QUOTED(lex->state)))
		ret = lex->index - 1;
	else if (lex->state == EXPAND)
	{
		if (match_expand(lex, token_start))
			ret = (lex->index - 1);
	}
	else if (lex->state == WORD)
	{
		if (match_word(lex))
			ret = (lex->index - 1);
	}
	else if (IS_QUOTED(lex->state))
	{
		if (lex->line[lex->index] == '\0')
		{
			if (lex->reopen)
				reopen_line_editing(lex);
			else
			{
				// Error, treat it
			}
		}
		if (charcmp(lex->line, lex->index, lex->state))
			ret = lex->index++;
	}
	return (ret);
}

int			token_match(t_lexer *lex, size_t token_start)
{
	int	ret;

	ret = -1;
	ret = match_part_1(lex, token_start);
	if (ret != -1)
		return (ret);
	else if (lex->state == OPERATOR)
	{
		if (IS_OPERATOR(lex->line[lex->index]) || \
				(charcmp(lex->line, lex->index, '-') && \
				charcmp(lex->line, lex->index - 1, '<')))
		{
			if (!match_operator(lex->line, token_start, lex->index))
				ret = lex->index - 1;
		}
		else
			ret = lex->index - 1;
	}
	if (lex->state == '\\')
		lex->state = WORD;
	return (ret);
}
