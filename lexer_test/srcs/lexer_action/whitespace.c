#include "lexer.h"
#include "libft.h"

void	lex_action_whitespace(t_lexer *lex, ssize_t **state_info)
{
	if (charcmp(lex->line, lex->pos, ' ') ||
				charcmp(lex->line, lex->pos, '	'))
		consume_input(lex, *state_info);
	else
		pop_state(lex, state_info);
}
