#include "syntax_coloring.h"
#include "lexer.h"
#include "libft.h"
#include <stdio.h>

int		lex_action_cmd_subst_le(t_lexer *lex, ssize_t **state_info, t_line *line)
{
	ssize_t	*info;

	info = lex->state->data;
	if (lex->line[lex->pos] == 0)
		return (FALSE);
	else if (lex->line[lex->pos] == '\\')
		push_state_le(lex, BS);
	else if (lex->line[info[_T_START]] == '`')
	{
		if (lex->line[lex->pos] == '`')
		{
			if (lex->pos - info[_T_START] == 0)
			{
				consume_input_le(lex, line);
			}
			else
			{
				pop_state_le(lex, state_info);
				consume_input_le(lex, line);
			}
		}
		else if (lex->line[lex->pos] == '"')
			push_state_le(lex, DQUOTES);
		else if (lex->line[lex->pos] == '\'')
			push_state_le(lex, QUOTES);
		else if (lex->line[lex->pos] == '$')
			push_state_le(lex, PARAM_EXP);
		else
			consume_input_le(lex, line);
	}
	else
	{
		if (lex->line[lex->pos] == '(')
		{
			(info[_T_NEST])++;
			consume_input_le(lex, line);
		}
		else if (lex->line[lex->pos] == '"')
			push_state_le(lex, DQUOTES);
		else if (lex->line[lex->pos] == '\'')
			push_state_le(lex, QUOTES);
		else if (lex->line[lex->pos] == '$')
			push_state_le(lex, PARAM_EXP);
		else if (lex->line[lex->pos] == ')')
		{
			if (info[_T_NEST] == 0)
			{
				consume_input_le(lex, line);
				pop_state_le(lex, state_info);
			}
			else
			{
				(info[_T_NEST])--;
				consume_input_le(lex, line);
			}
		}
		else 
			consume_input_le(lex, line);
	}
	return (TRUE);
}
