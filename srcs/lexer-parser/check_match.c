/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_match.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 15:03:19 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/23 17:05:06 by ade-sede         ###   ########.fr       */
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

static int	part_1(t_lexer *lex, size_t token_start)
{
	int		ret;

	ret = -1;
	if (IS_INPUT_END(lex->line[lex->index]))
	{
		ret = lex->index - 1;
	}
	else if (lex->state == EXPAND)
	{
		if (match_expand(lex, token_start))
			ret = (lex->index - 1);
	}
	else if (lex->state == WORD)
	{
		if (match_word(lex))
			ret = (lex->index - 1);
	}
	else if (IS_QUOTED(lex->state))
	{
		if (charcmp(lex->line, lex->index, lex->state))
		{
			ret = lex->index++;
		}
	}
	return (ret);
}

int			token_match(t_lexer *lex, size_t token_start)
{
	int	ret;

	ret = -1;
	ret = part_1(lex, token_start);
	if (ret != -1)
		return (ret);
	else if (lex->state == OPERATOR)
	{
		if (IS_OPERATOR(lex->line[lex->index]) || \
				(charcmp(lex->line, lex->index, '-') && \
charcmp(lex->line, lex->index - 1, '<')))
		{
			if (!match_operator(lex->line, token_start, lex->index))
				ret = lex->index - 1;
		}
		else
			ret = lex->index - 1;
	}
	if (lex->state == '\\')
		lex->state = WORD;
	return (ret);
}
