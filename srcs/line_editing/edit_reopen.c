#include "line_editing.h"
#include "failure.h"
#include "t_lexer.h"
#include "history.h"
#include "exec.h"
#include "lexer.h"

void		reopen_line_editing(t_lexer *lex, int res_lexer, int res_parser)
{
	char	*new_command;
	t_line	*line;
	t_env	*env;

	env = singleton_env();
	line = singleton_line();
	if (res_parser == TK_PIPE)
		load_prompt(env, line, NULL, "pipe> ");
	else if (res_parser == TK_AND_IF)
		load_prompt(env, line, NULL, "cmdand> ");
	else if (res_parser == TK_OR_IF)
		load_prompt(env, line, NULL, "cmdor> ");
	else if (res_lexer == '"')
		load_prompt(env, line, NULL, "dquote> ");
	else if (res_lexer == '\'')
		load_prompt(env, line, NULL, "quote> ");
	new_command = line_editing_get_input(line, \
			singleton_hist(), &edit_set_signals_reopen);
	lex->line = ft_strchange((char*)lex->line, \
			ft_strjoin((char*)lex->line, new_command));
}
