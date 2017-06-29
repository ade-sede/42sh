/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 18:01:22 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/26 16:01:14 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <stdio.h>

/*
**	Returns the state according to char lex->line[lex->index]
**	Everything that is not Quoted (simple or double) Blackslashed, or a
**	candidate to expansion is considered to be at the default state 'word'.
*/

int		update_state(t_lexer *lex)
{
	if (charcmp(lex->line, lex->index, '\\'))
		return (lex->line[lex->index]);
	if (IS_QUOTED(lex->line[lex->index]))
		return (lex->line[lex->index]);
	else if (IS_OPERATOR(lex->line[lex->index]))
		return (OPERATOR);
	else if (IS_EXPAND(lex->line[lex->index]))
		return (EXPAND);
	if (!lex->line[lex->index])
		return (INPUT_END);
	return (WORD);
}
