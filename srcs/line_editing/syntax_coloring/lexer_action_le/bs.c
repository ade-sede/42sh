/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bs.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:37 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:36 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "syntax_coloring.h"
#include "lexer.h"

int		lex_action_bs_le(t_lexer *lex, struct s_info **state_info, t_line *line)
{
	struct s_info *info;

	info = lex->state->data;
	if (lex->line[lex->pos] == 0)
		return (FALSE);
	else if (info->count == 2)
	{
		if (info->value.str[1] == '\n' && lex->line[lex->pos] == 0)
			return (FALSE);
		pop_state_le(lex, state_info);
	}
	else
		consume_input_le(lex, line);
	return (TRUE);
}
