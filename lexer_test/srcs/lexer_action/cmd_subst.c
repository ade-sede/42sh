#include "lexer.h"
#include "libft.h"

#include <stdio.h>
int		lex_action_cmd_subst(t_lexer *lex, ssize_t **state_info)
{
	ssize_t	*info;

	info = lex->state->data;
	if (lex->line[lex->pos] == 0)
		return (FALSE);
	else if (lex->line[lex->pos] == '\\')
		push_state(lex, BS);
	else if (lex->line[info[_T_START]] == '`')
	{
		if (lex->line[lex->pos] == '`')
		{
			if (info[_T_COUNT] == 0)
			{
				consume_input(lex);
			}
			else
			{
				pop_state(lex, state_info);
				consume_input(lex);
			}
		}
		else if (lex->line[lex->pos] == '"')
			push_state(lex, DQUOTES);
		else if (lex->line[lex->pos] == '\'')
			push_state(lex, QUOTES);
		else if (lex->line[lex->pos] == '$')
			push_state(lex, PARAM_EXP);
		else
			consume_input(lex);
	}
	else
	{
		if (lex->line[lex->pos] == '(')
		{
			(info[_T_NEST])++;
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
			if (info[_T_NEST] == 0)
			{
				consume_input(lex);
				pop_state(lex, state_info);
			}
			else
			{
				(info[_T_NEST])--;
				consume_input(lex);
			}
		}
		else 
			consume_input(lex);
	}
	return (TRUE);
}
