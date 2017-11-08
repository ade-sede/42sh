#include "libft.h"
#include "lexer.h"

int		lex_action_bs(t_lexer *lex, ssize_t **state_info)
{
	ssize_t	*info;

	info = lex->state->data;
	if (info[_T_COUNT] == 2)
	{
		if (lex->line[info[_T_START] + 1] == '\n' && lex->line[lex->pos] == 0)
			return (FALSE);
		pop_state(lex, state_info);
	}
	else
		consume_input(lex);
	return (TRUE);
}
