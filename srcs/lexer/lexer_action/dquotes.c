#include "lexer.h"
#include "libft.h"

int		lex_action_dquotes(t_lexer *lex, ssize_t **state_info)
{
	ssize_t	*info;

	if (lex->line[lex->pos] == 0)
		return (FALSE);
	if (lex->line[lex->pos] == '\\')
		push_state(lex, BS);
	else if (lex->line[lex->pos] ==  '"')
	{
		info = lex->state->data;
		if (lex->pos - info[_T_START] != 0)
		{
			consume_input(lex);
			pop_state(lex, state_info);
		}
		else
			consume_input(lex);
	}
	else if (lex->line[lex->pos] == '$')
		push_state(lex, PARAM_EXP);
	else if (lex->line[lex->pos] == '`')
		push_state(lex, CMD_SUBST);
	else
		consume_input(lex);
	return (TRUE);
}
