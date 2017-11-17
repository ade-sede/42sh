#include "syntax_coloring.h"
#include "lexer.h"
#include "libft.h"

int		lex_action_comment_le(t_lexer *lex, ssize_t **state_info, t_line *line)
{
	if (lex->line[lex->pos] == 0)
		pop_state_le(lex, state_info);
	else if (lex->line[lex->pos] == '\n')
	{
		consume_input_le(lex, line);
		pop_state_le(lex, state_info);
	}
	else
		consume_input_le(lex, line);
	return (TRUE);
}
