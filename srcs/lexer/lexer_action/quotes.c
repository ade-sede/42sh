#include "libft.h"
#include "lexer.h"

int		lex_action_quotes(t_lexer *lex, ssize_t **state_info)
{
	ssize_t	*info;

	if (lex->line[lex->pos] == 0)
		return (FALSE);
	else if (lex->line[lex->pos] ==  '\'')
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
	else
		consume_input(lex);
	return (TRUE);
}
