/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bs.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 19:51:23 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/23 19:51:24 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"

int		lex_action_bs(t_lexer *lex, struct s_info **state_info)
{
	struct s_info *info;

	info = lex->state->data;
	if (lex->line[lex->pos] == 0)
		return (FALSE);
	else if (info->count == 2)
	{
		if (info->value.str[1] == '\n' && lex->line[lex->pos] == 0)
			return (FALSE);
		pop_state(lex, state_info);
	}
	else
		consume_input(lex);
	return (TRUE);
}
