/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 16:44:43 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/04 17:06:00 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <stdio.h>

/*
**	Initialize the token_start index on the right character and returns the new
**	lexer state depending on the current one
*/

int		start_token(t_lexer *lex, size_t *token_start)
{
	if (!IS_QUOTED(lex->state))
		while (lex->line[lex->index] && IS_WHITESPACE(lex->line[lex->index]))
			lex->index++;
	*token_start = lex->index;
	if (IS_QUOTED(lex->state))
	{
		printf("%zu\n", lex->index);//			REMOVE		
		if (IS_QUOTED(lex->line[lex->index - 1]))
		{
			lex->index++;
			return (DEFAULT);
		}
		else
			return (lex->state);
	}
	else if (IS_QUOTED(lex->line[lex->index]))
	{
		if (IS_QUOTED(lex->state))
		{
			if(lex->state == (unsigned char)lex->line[lex->index])
			{
				lex->index++;
				return (DEFAULT);
			}
		}
		else
			return (lex->line[lex->index++]);
	}
	else if (IS_WORD(lex->line[lex->index]))
	{
		return (WORD);
	}
	return (DEFAULT);
}
