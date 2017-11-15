#include "syntax_coloring.h"
#include "lexer.h"
#include "libft.h"

int		lex_action_newline_le(t_lexer *lex, ssize_t **state_info, t_line *line)
{
	consume_input_le(lex, line);
	pop_state_le(lex, state_info);
	return (TRUE);
}
