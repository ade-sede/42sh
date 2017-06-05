/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_match.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 15:03:19 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/05 16:16:23 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <stdio.h>

/*
**	Determines if the char we are reading should or not be included in the
**	token.
**	If not, it closes the last token by returning the index of its last char,
**	and putting lex->index on the first char of the next potential token.
*/

int		token_match(t_lexer *lex, size_t token_start)
{
	/* printf("Trying to match with char %c on index %zu with state %d \n", lex->line[lex->index], lex->index, lex->state);//			REMOVE */		
	if (IS_INPUT_END(lex->line[lex->index]))
	{
		/* printf("yop\n"); */
		return (lex->index - 1);
	}
	else if (IS_QUOTED(lex->state))
	{
		/* printf("1\n"); */
		if (charcmp(lex->line, lex->index, lex->state))
			return (lex->index++);
	}
	else if (lex->state == OPERATOR)
	{
		/* printf("state recognised as OPERATOR\n"); */
		if (IS_OPERATOR(lex->line[lex->index]) || (charcmp(lex->line, lex->index, '-') && charcmp(lex->line, lex->index - 1, '<')))
		{
			/* printf("char recognised as OPERATOR\n"); */
			if (!match_operator(lex->line, token_start, lex->index, NULL))
				return (lex->index - 1);
		}
		else
			return (lex->index - 1);
	}
	else if (lex->state == WORD)
	{
		/* printf("2\n"); */
		if (!IS_WORD(lex->line[lex->index]))
			return (lex->index - 1);
	}
	else if (IS_WHITESPACE(lex->line[lex->index]))
		return (lex->index - 1);
	/* printf("Casual return\n"); */
	return (-1);
}
