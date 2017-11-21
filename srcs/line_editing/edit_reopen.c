#include "line_editing.h"
#include "parser.h"
#include "failure.h"
#include "t_lexer.h"
#include "exec.h"
#include "t_history.h"
#include "lexer.h"

char	*join_prompt(char *parser_prompt, char *lexer_prompt)
{
	if (parser_prompt && lexer_prompt)
		return (ft_strjoin3_free(parser_prompt, " ", lexer_prompt, 5));
	else if (parser_prompt)
		return (parser_prompt);
	else if (lexer_prompt)
		return (lexer_prompt);
	return (ft_strdup("$>"));

}

void		reopen_line_editing(t_lexer *lex, t_parser *parser, char **new_command)
{
	t_line	*line;
	t_env	*env;
	char	*parser_prompt;
	char	*lexer_prompt;
	char	*prompt;

	parser_prompt = parser_construct_prompt(parser->ast_stack);
	lexer_prompt = lexer_construct_prompt(lex);

	prompt = join_prompt(parser_prompt, lexer_prompt);
	prompt = ft_strjoin_free(prompt, "> ", 2);

	env = singleton_env();
	line = singleton_line();
	load_prompt(env, line, NULL, prompt);
	*new_command = line_editing_get_line(line, \
			singleton_history(), &edit_set_signals_reopen);
}
