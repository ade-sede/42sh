/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 05:07:29 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 05:08:37 by vcombey          ###   ########.fr       */
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
