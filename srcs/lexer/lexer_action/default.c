/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 20:10:09 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/23 20:12:57 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

int		lex_action_default(t_lexer *lex, struct s_info **state_info)
{
	if (lex->line[lex->pos] == 0)
		return (TRUE);
	if (lex->line[lex->pos] == ' ' || lex->line[lex->pos] == '\t')
		push_state(lex, WHITESPACE);
	else if (lex->line[lex->pos] == '\n')
		push_state(lex, NEWLINE);
	else if (CHAR_IS_OPERATOR(lex->line[lex->pos]))
		push_state(lex, OPERATOR);
	else if (lex->line[lex->pos] == '#')
		push_state(lex, COMMENT);
	else
		push_state(lex, WORD);
	(void)state_info;
	return (TRUE);
}
