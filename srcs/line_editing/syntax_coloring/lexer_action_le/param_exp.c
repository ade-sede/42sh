/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:37 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:38 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "syntax_coloring.h"
#include "lexer.h"

int		lex_action_param_exp_p2_le(t_lexer *lex, struct s_info **state_info,\
		struct s_info *info, t_line *line)
{
	if (lex->line[lex->pos] == '`')
		pop_state_le(lex, state_info);
	else if (lex->line[lex->pos] == '\n')
		pop_state_le(lex, state_info);
	else if (lex->line[lex->pos] == ')')
		pop_state_le(lex, state_info);
	else if (lex->line[lex->pos] == '(')
	{
		if (info->count == 1)
		{
			change_state(lex, CMD_SUBST);
			consume_input_le(lex, line);
		}
		else
			pop_state_le(lex, state_info);
	}
	else
		consume_input_le(lex, line);
	return (TRUE);
}

int		lex_action_param_exp_le(t_lexer *lex, struct s_info **state_info, \
		t_line *line)
{
	struct s_info *info;

	info = lex->state->data;
	if (lex->line[lex->pos] == 0)
		pop_state_le(lex, state_info);
	else if (lex->line[lex->pos] == '\\')
		push_state_le(lex, BS);
	else if (lex->line[lex->pos] == '\'')
		push_state_le(lex, QUOTES);
	else if (lex->line[lex->pos] == ' ' || lex->line[lex->pos] == '\t')
		pop_state_le(lex, state_info);
	else if (CHAR_IS_OPERATOR(lex->line[lex->pos]))
		pop_state_le(lex, state_info);
	else if (lex->line[lex->pos] == '"')
		pop_state_le(lex, state_info);
	else
		lex_action_param_exp_p2_le(lex, state_info, info, line);
	return (TRUE);
}
