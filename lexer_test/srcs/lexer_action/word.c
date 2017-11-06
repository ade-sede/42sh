#include "lexer.h"
#include "libft.h"

void	lex_action_word(t_lexer *lex, ssize_t **state_info)
{
	if (lex->line[lex->pos] == 0)
		pop_state(lex, state_info);
	else if (charcmp(lex->line, lex->pos, ' ') || \
			charcmp(lex->line, lex->pos, '	'))
		pop_state(lex, state_info);
	else
		consume_input(lex, *state_info);
}
