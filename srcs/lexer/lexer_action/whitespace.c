#include "lexer.h"
#include "libft.h"

#include <stdio.h>
int		lex_action_whitespace(t_lexer *lex, ssize_t **state_info)
{
	if (lex->line[lex->pos] == ' ' || lex->line[lex->pos] == '\t' )
		consume_input(lex);
	else
		pop_state(lex, state_info);
	return (TRUE);
}
