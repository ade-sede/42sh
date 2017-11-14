#include "syntax_coloring.h"
#include "lexer.h"
#include "libft.h"

int		lex_action_dquotes_le(t_lexer *lex, ssize_t **state_info, t_line *line)
{
	ssize_t	*info;

	if (lex->line[lex->pos] == 0)
		return (FALSE);
	if (lex->line[lex->pos] == '\\')
		push_state_le(lex, BS);
	else if (lex->line[lex->pos] ==  '"')
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
	else if (lex->line[lex->pos] == '$')
		push_state_le(lex, PARAM_EXP);
	else if (lex->line[lex->pos] == '`')
		push_state_le(lex, CMD_SUBST);
	else
		consume_input_le(lex, line);
	return (TRUE);
}
