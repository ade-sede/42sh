/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_match.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 15:03:19 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/05 18:46:06 by ade-sede         ###   ########.fr       */
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
	int	ret;
	
	ret = 0;

	if (IS_INPUT_END(lex->line[lex->index]))
		return (lex->index - 1);
	else if (lex->state == EXPAND)
	{
	}
	else if (lex->state == WORD)
	{
		if (check_word_end(lex))
			return (lex->index - 1);
	}
	else if (IS_QUOTED(lex->state))
	{
		if (charcmp(lex->line, lex->index, lex->state))
			return (lex->index++);
	}
	else if (lex->state == OPERATOR)
	{
		if (IS_OPERATOR(lex->line[lex->index]) || (charcmp(lex->line, lex->index, '-') && charcmp(lex->line, lex->index - 1, '<')))
		{
			if (!match_operator(lex->line, token_start, lex->index, NULL))
				return (lex->index - 1);
		}
		else
			return (lex->index - 1);
	}
	else if (IS_WHITESPACE(lex->line[lex->index]))
		return (lex->index - 1);
	return (-1);
}


/*
**	As the default state is word, we need to check if char we are reading is
**	starting a new token, thus closing the current one.
*/
int		check_word_end(t_lexer *lex)
{
	if (IS_WHITESPACE(lex->line[lex->index]))
		return (1);
	else if (update_state(lex) != WORD)
		return (1);
	return (0);
}

int		check_expand_end(t_lexer *lex, size_t token_start)
{
	if (lex->line[token_start] == '`')
		;
	return (0);
}
