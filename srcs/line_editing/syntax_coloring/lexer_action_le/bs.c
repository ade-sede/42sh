#include "syntax_coloring.h"
#include "libft.h"
#include "lexer.h"

int		lex_action_bs_le(t_lexer *lex, ssize_t **state_info, t_line *line)
{
	ssize_t	*info;

	info = lex->state->data;
	if (lex->line[lex->pos] == 0)
		return (FALSE);
	if (lex->pos - info[_T_START] == 2)
	{
		if (lex->line[info[_T_START] + 1] == '\n' && lex->line[lex->pos] == 0)
			return (FALSE);
		pop_state_le(lex, state_info);
	}
	else
		consume_input_le(lex, line);
	return (TRUE);
}
