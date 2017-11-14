#include "libft.h"
#include "lexer.h"

int		lex_action_param_exp(t_lexer *lex, ssize_t **state_info)
{
	ssize_t	*info;

	info = lex->state->data;
	if (lex->line[lex->pos] == 0)
		pop_state(lex, state_info);
	else if (lex->line[lex->pos] == '\\')
		push_state(lex, BS);
	else if (lex->line[lex->pos] == '\'')
		push_state(lex, QUOTES);
	else if (lex->line[lex->pos] == ' ' || lex->line[lex->pos] == '\t')
		pop_state(lex, state_info);
	else if (CHAR_IS_OPERATOR(lex->line[lex->pos]))
		pop_state(lex, state_info);
	else if (lex->line[lex->pos] == '"')
		pop_state(lex, state_info);
	else if (lex->line[lex->pos] == '`')
		pop_state(lex, state_info);
	else if (lex->line[lex->pos] == '\n')
		pop_state(lex, state_info);
	else if (lex->line[lex->pos] == ')')
		pop_state(lex, state_info);
	else if (lex->line[lex->pos] == '(')
	{
		if (lex->pos - info[_T_START] == 1)
		{
			change_state(lex, CMD_SUBST);
			consume_input(lex);
		}
		else
			pop_state(lex, state_info);
	}
	else
		consume_input(lex);
	return (TRUE);
}
