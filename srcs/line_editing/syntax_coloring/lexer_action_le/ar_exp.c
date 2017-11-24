/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar_exp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 20:06:45 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 12:34:30 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "syntax_coloring.h"
#include "libft.h"
#include <stdio.h>

int		lex_action_ar_exp_p2_le(t_lexer *lex, struct s_info **state_info,\
		struct s_info *info, t_line *line)
{
	if (lex->line[lex->pos] == '\'')
		push_state_le(lex, QUOTES);
	else if (lex->line[lex->pos] == '$')
		push_state_le(lex, PARAM_EXP);
	else if (lex->line[lex->pos] == ')')
	{
		if (info->nest == -1)
		{
			consume_input_le(lex, line);
			pop_state_le(lex, state_info);
		}
		else
		{
			info->nest--;
			consume_input_le(lex, line);
		}
	}
	else
		consume_input_le(lex, line);
	return (TRUE);
}

int		lex_action_ar_exp_le(t_lexer *lex, struct s_info **state_info, \
		t_line *line)
{
	struct s_info *info;

	info = lex->state->data;
	if (lex->line[lex->pos] == 0)
		return (FALSE);
	else if (lex->line[lex->pos] == '\\')
		push_state_le(lex, BS);
	else if (lex->line[lex->pos] == '(')
	{
		info->nest++;
		consume_input_le(lex, line);
	}
	else if (lex->line[lex->pos] == '"')
		push_state_le(lex, DQUOTES);
	else
		lex_action_ar_exp_p2_le(lex, state_info, info, line);
	return (TRUE);
}
