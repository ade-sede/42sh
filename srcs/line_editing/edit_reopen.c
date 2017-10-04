#include "line_editing.h"
#include "failure.h"
#include "t_lexer.h"
#include "history.h"
#include "exec.h"
#include "lexer.h"

void		append_history(char *command)
{
	t_hist		*h;
	t_list_d	*list;
	char		*full_command;

	h = singleton_hist();
	list = h->list->first;
	command[ft_strlen(command) - 1] = 0;
	full_command = ft_strjoin(list->data, command);
	list->data = ft_strchange(list->data, full_command);
}


void		reopen_line_editing(t_lexer *lex, int caller)
{
	char	*new_command;

	if (caller == 0)
		load_prompt(singleton_env(), singleton_line(), "PS2", "> ");
	else if (lex->state == '"')
		load_prompt(singleton_env(), singleton_line(), "PS2", "dquote> ");
	else if (lex->state == '\'')
		load_prompt(singleton_env(), singleton_line(), "PS3", "dquote> ");
	
	new_command = ft_strdup(line_editing_get_input(singleton_line(), \
			singleton_hist(), &edit_set_signals_reopen));
	/* new_command = ft_strchange(new_command, ft_strjoin(new_command, "\n")); */
	lex->line = ft_strchange((char*)lex->line, \
			ft_strjoin((char*)lex->line, new_command));
	append_history(new_command);
	free(new_command);
}
