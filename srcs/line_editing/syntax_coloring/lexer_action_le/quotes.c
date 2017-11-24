/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 20:02:42 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 12:36:27 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "syntax_coloring.h"
#include "lexer.h"

int		lex_action_quotes_le(t_lexer *lex, struct s_info **state_info, \
		t_line *line)
{
	struct s_info *info;

	if (lex->line[lex->pos] == 0)
		return (FALSE);
	else if (lex->line[lex->pos] == '\'')
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
	else
		consume_input_le(lex, line);
	return (TRUE);
}
