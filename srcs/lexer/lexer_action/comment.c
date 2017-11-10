#include "lexer.h"
#include "libft.h"

int		lex_action_comment(t_lexer *lex, ssize_t **state_info)
{
	if (lex->line[lex->pos] == 0)
		pop_state(lex, state_info);
	else if (lex->line[lex->pos] == '\n')
	{
		consume_input(lex);
		pop_state(lex, state_info);
	}
	else
		consume_input(lex);
	return (TRUE);
}
