#include "libft.h"
#include "lexer.h"

int		lex_action_bs(t_lexer *lex, struct s_info **state_info)
{
	struct s_info *info;

	info = lex->state->data;
	if (lex->line[lex->pos] == 0)
		return (FALSE);
	/* else if (lex->pos - info[_T_START] == 2) */
	else if (lex->pos - info->start == 2)
	{
		/* if (lex->line[info[_T_START] + 1] == '\n' && lex->line[lex->pos] == 0) */
		if (lex->line[info->start + 1] == '\n' && lex->line[lex->pos] == 0)
			return (FALSE);
		pop_state(lex, state_info);
	}
	else
		consume_input(lex);
	return (TRUE);
}
