#include "lexer.h"
#include "libft.h"

int		lex_action_default(t_lexer *lex, struct s_info **state_info)
{
	if (lex->line[lex->pos] == 0)
		return (TRUE);
	if (lex->line[lex->pos] == ' ' || lex->line[lex->pos] == '\t')
		push_state(lex, WHITESPACE);
	else if (lex->line[lex->pos] == '\n')
		push_state(lex, NEWLINE);
	else if (CHAR_IS_OPERATOR(lex->line[lex->pos]))
		push_state(lex, OPERATOR);
/*
**		else if (lex->line[lex->pos] == '"')
**			push_state(lex, DQUOTES);
*/
	/*
**		else if (lex->line[lex->pos] == '\'')
**			push_state(lex, QUOTES);
*/
	else if (lex->line[lex->pos] == '#')
		push_state(lex, COMMENT);
	else
		push_state(lex, WORD);
	(void)state_info;
	return (TRUE);
}
