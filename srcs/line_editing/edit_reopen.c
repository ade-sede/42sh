#include "line_editing.h"
#include "failure.h"
#include "t_lexer.h"
#include "history.h"
#include "exec.h"
#include "lexer.h"

void		reopen_line_editing(t_lexer *lex, int res_lexer, int res_parser)
{
	char	*new_command;

	if (res_parser == TK_PIPE)
		load_prompt(singleton_env(), singleton_line(), "", "pipe> ");
	else if (res_parser == TK_AND)
		load_prompt(singleton_env(), singleton_line(), "", "cmdand> ");
	else if (res_lexer == '"')
		load_prompt(singleton_env(), singleton_line(), "PS2", "dquote> ");
	else if (res_lexer == '\'')
		load_prompt(singleton_env(), singleton_line(), "PS3", "dquote> ");
	new_command = ft_strdup(line_editing_get_input(singleton_line(), \
			singleton_hist(), &edit_set_signals_reopen));
	lex->line = ft_strchange((char*)lex->line, \
			ft_strjoin((char*)lex->line, new_command));
	free(new_command);
}
