#include "syntax_coloring.h"
#include "lexer.h"
#include "libft.h"

#include <stdio.h>
int		lex_action_whitespace_le(t_lexer *lex, ssize_t **state_info, t_line *line)
{
	if (lex->line[lex->pos] == ' ' || lex->line[lex->pos] == '\t' )
		consume_input_le(lex, line);
	else
		pop_state_le(lex, state_info);
	return (TRUE);
}
