/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquotes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:37 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:38 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "syntax_coloring.h"
#include "libft.h"

int		lex_action_dquotes_le(t_lexer *lex, struct s_info **state_info, \
		t_line *line)
{
	struct s_info *info;

	if (lex->line[lex->pos] == 0)
		return (FALSE);
	if (lex->line[lex->pos] == '\\')
		push_state_le(lex, BS);
	else if (lex->line[lex->pos] == '"')
	{
		info = lex->state->data;
		if (info->count != 0)
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
