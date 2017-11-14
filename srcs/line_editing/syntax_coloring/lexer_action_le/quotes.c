#include "syntax_coloring.h"
#include "libft.h"
#include "lexer.h"

int		lex_action_quotes_le(t_lexer *lex, ssize_t **state_info, t_line *line)
{
	ssize_t	*info;

	if (lex->line[lex->pos] == 0)
		return (FALSE);
	if (lex->line[lex->pos] == '\\')
		push_state_le(lex, BS);
	else if (lex->line[lex->pos] ==  '\'')
	{
		info = lex->state->data;
		if (info[_T_COUNT] != 0)
		{
			consume_input_le(lex, line);
			pop_state_le(lex, state_info);
		}
		else
			consume_input_le(lex, line);
	}
	else
		consume_input_le(lex, line);
	return (TRUE);
}
