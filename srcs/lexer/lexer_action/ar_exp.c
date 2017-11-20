#include "lexer.h"
#include "libft.h"
#include <stdio.h>

int		lex_action_ar_exp(t_lexer *lex, struct s_info **state_info)
{
	struct s_info *info;

	info = lex->state->data;
	if (lex->line[lex->pos] == 0)
		return (FALSE);
	else if (lex->line[lex->pos] == '\\')
		push_state(lex, BS);
	else if (lex->line[lex->pos] == '(')
	{
		info->nest++;
		consume_input(lex);
	}
	else if (lex->line[lex->pos] == '"')
		push_state(lex, DQUOTES);
	else if (lex->line[lex->pos] == '\'')
		push_state(lex, QUOTES);
	else if (lex->line[lex->pos] == '$')
		push_state(lex, PARAM_EXP);
	else if (lex->line[lex->pos] == ')')
	{
		/* if (info[_T_NEST] == 0) */
		if (info->nest == 0)
		{
			consume_input(lex);
			pop_state(lex, state_info);
		}
		else
		{
			/* (info[_T_NEST])--; */
			info->nest--;
			consume_input(lex);
		}
	}
	else 
		consume_input(lex);
	return (TRUE);
}
