/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:37 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:27 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

int		lex_action_comment(t_lexer *lex, struct s_info **state_info)
{
	if (lex->line[lex->pos] == 0)
		pop_state(lex, state_info);
	else if (lex->line[lex->pos] == '\n')
	{
		consume_input(lex);
		pop_state(lex, state_info);
	}
	else
		consume_input(lex);
	return (TRUE);
}
