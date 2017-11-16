#include "syntax_coloring.h"
#include "lexer.h"
#include "libft.h"

#include <stdio.h>
int		lex_action_word_le(t_lexer *lex, ssize_t **state_info, t_line *line)
{
	ssize_t	*info;

	if (lex->line[lex->pos] == 0)
		pop_state_le(lex, state_info);
	if (lex->line[lex->pos] == '\\')
		push_state_le(lex, BS);
	else if (lex->line[lex->pos] == '\n')
		pop_state_le(lex, state_info);
	else if (lex->line[lex->pos] == '(' || lex->line[lex->pos] == ')')
	{
		info = lex->state->data;
		if (lex->pos - info[_T_START] != 0)
			pop_state_le(lex, state_info);
		else
		{
			consume_input_le(lex, line);
			pop_state_le(lex, state_info);
		}
	}
	else if (CHAR_IS_OPERATOR(lex->line[lex->pos]))
		pop_state_le(lex, state_info);
	else if (lex->line[lex->pos] == ' ' || lex->line[lex->pos] == '\t' )
		pop_state_le(lex, state_info);
	else if (lex->line[lex->pos] == '"')
		push_state_le(lex, DQUOTES);
	else if (lex->line[lex->pos] == '\'')
		push_state_le(lex, QUOTES);
	else if (lex->line[lex->pos] == '#')
		pop_state_le(lex, state_info);
	else if (lex->line[lex->pos] == '$')
		push_state_le(lex, PARAM_EXP);
	else if (lex->line[lex->pos] == '`')
		push_state_le(lex, CMD_SUBST);
	else
		consume_input_le(lex, line);
	return (TRUE);
}
