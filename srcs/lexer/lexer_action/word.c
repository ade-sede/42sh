/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 19:42:03 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/23 19:50:18 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

static int		lex_action_word_p2(t_lexer *lex, struct s_info **state_info)
{
	if (lex->line[lex->pos] == ' ' || lex->line[lex->pos] == '\t')
		pop_state(lex, state_info);
	else if (lex->line[lex->pos] == '"')
		push_state(lex, DQUOTES);
	else if (lex->line[lex->pos] == '\'')
		push_state(lex, QUOTES);
	else if (lex->line[lex->pos] == '#')
		pop_state(lex, state_info);
	else if (lex->line[lex->pos] == '$')
		push_state(lex, PARAM_EXP);
	else if (lex->line[lex->pos] == '`')
		push_state(lex, CMD_SUBST);
	else
		consume_input(lex);
	return (TRUE);
}

int				lex_action_word(t_lexer *lex, struct s_info **state_info)
{
	struct s_info *info;

	if (lex->line[lex->pos] == 0)
		pop_state(lex, state_info);
	else if (lex->line[lex->pos] == '\\')
		push_state(lex, BS);
	else if (lex->line[lex->pos] == '\n')
		pop_state(lex, state_info);
	else if (lex->line[lex->pos] == '(' || lex->line[lex->pos] == ')')
	{
		info = lex->state->data;
		if (info->count != 0)
			pop_state(lex, state_info);
		else
		{
			consume_input(lex);
			pop_state(lex, state_info);
		}
	}
	else if (CHAR_IS_OPERATOR(lex->line[lex->pos]))
		pop_state(lex, state_info);
	else
		return (lex_action_word_p2(lex, state_info));
	return (TRUE);
}
