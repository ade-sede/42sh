/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:37 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:29 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"

int		lex_action_quotes(t_lexer *lex, struct s_info **state_info)
{
	struct s_info *info;

	if (lex->line[lex->pos] == 0)
		return (FALSE);
	else if (lex->line[lex->pos] == '\'')
	{
		info = lex->state->data;
		if (info->count != 0)
		{
			consume_input(lex);
			pop_state(lex, state_info);
		}
		else
			consume_input(lex);
	}
	else
		consume_input(lex);
	return (TRUE);
}
