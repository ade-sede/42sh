#include "lexer.h"
#include "libft.h"

#include <stdio.h>
int		lex_action_word(t_lexer *lex, ssize_t **state_info)
{
	ssize_t	*info;

	if (lex->line[lex->pos] == 0)
		pop_state(lex, state_info);
	if (lex->line[lex->pos] == '\\')
		push_state(lex, BS);
	else if (lex->line[lex->pos] == '\n')
		pop_state(lex, state_info);
	else if (lex->line[lex->pos] == '(' || lex->line[lex->pos] == ')')
	{
		info = lex->state->data;
		if (info[_T_COUNT] != 0)
			pop_state(lex, state_info);
		else
		{
			consume_input(lex);
			pop_state(lex, state_info);
		}
	}
	else if (CHAR_IS_OPERATOR(lex->line[lex->pos]))
		pop_state(lex, state_info);
	else if (lex->line[lex->pos] == '\'' || lex->line[lex->pos] == '"' )
		pop_state(lex, state_info);
	else if (lex->line[lex->pos] == ' ' || lex->line[lex->pos] == '\t' )
		pop_state(lex, state_info);
	else if (lex->line[lex->pos] == '#')
		pop_state(lex, state_info);
	else if (lex->line[lex->pos] == '$')
		push_state(lex, PARAM_EXP);
	else if (lex->line[lex->pos] == '`')
		push_state(lex, CMD_SUBST);
	else
		consume_input(lex);
	return (TRUE);
}
