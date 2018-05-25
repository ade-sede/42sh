/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:37 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:39 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "syntax_coloring.h"

static int		lex_action_word_p2_le(t_lexer *lex, \
		struct s_info **state_info, t_line *line)
{
	if (lex->line[lex->pos] == ' ' || lex->line[lex->pos] == '\t')
		pop_state_le(lex, state_info);
	else if (lex->line[lex->pos] == '"')
		push_state_le(lex, DQUOTES);
	else if (lex->line[lex->pos] == '\'')
		push_state_le(lex, QUOTES);
	else if (lex->line[lex->pos] == '#')
		pop_state_le(lex, state_info);
	else if (lex->line[lex->pos] == '$')
		push_state_le(lex, PARAM_EXP);
	else if (lex->line[lex->pos] == '`')
		push_state_le(lex, CMD_SUBST);
	else
		consume_input_le(lex, line);
	return (TRUE);
}

int				lex_action_word_le(t_lexer *lex, struct s_info **state_info, \
		t_line *line)
{
	struct s_info *info;

	if (lex->line[lex->pos] == 0)
		pop_state_le(lex, state_info);
	else if (lex->line[lex->pos] == '\\')
		push_state_le(lex, BS);
	else if (lex->line[lex->pos] == '\n')
		pop_state_le(lex, state_info);
	else if (lex->line[lex->pos] == '(' || lex->line[lex->pos] == ')')
	{
		info = lex->state->data;
		if (info->count != 0)
			pop_state_le(lex, state_info);
		else
		{
			consume_input_le(lex, line);
			pop_state_le(lex, state_info);
		}
	}
	else if (CHAR_IS_OPERATOR(lex->line[lex->pos]))
		pop_state_le(lex, state_info);
	else
		return (lex_action_word_p2_le(lex, state_info, line));
	return (TRUE);
}
