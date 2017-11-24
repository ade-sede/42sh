/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:37 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:28 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"

int		lex_action_param_exp_p2(t_lexer *lex, struct s_info **state_info,\
		struct s_info *info)
{
	if (lex->line[lex->pos] == '`')
		pop_state(lex, state_info);
	else if (lex->line[lex->pos] == '\n')
		pop_state(lex, state_info);
	else if (lex->line[lex->pos] == ')')
		pop_state(lex, state_info);
	else if (lex->line[lex->pos] == '(')
	{
		if (info->count == 1)
		{
			change_state(lex, CMD_SUBST);
			consume_input(lex);
		}
		else
			pop_state(lex, state_info);
	}
	else
		consume_input(lex);
	return (TRUE);
}

int		lex_action_param_exp(t_lexer *lex, struct s_info **state_info)
{
	struct s_info *info;

	info = lex->state->data;
	if (lex->line[lex->pos] == 0)
		pop_state(lex, state_info);
	else if (lex->line[lex->pos] == '\\')
		push_state(lex, BS);
	else if (lex->line[lex->pos] == '\'')
		push_state(lex, QUOTES);
	else if (lex->line[lex->pos] == ' ' || lex->line[lex->pos] == '\t')
		pop_state(lex, state_info);
	else if (CHAR_IS_OPERATOR(lex->line[lex->pos]))
		pop_state(lex, state_info);
	else if (lex->line[lex->pos] == '"')
		pop_state(lex, state_info);
	else
		lex_action_param_exp_p2(lex, state_info, info);
	return (TRUE);
}
