/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:40:47 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/11 22:40:59 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

/*
**	This function looks for the match of expand sequences. If the
**	expansion/substitution uses the `$(', `$((' or `${' notation, we shall look
**	for its end using a loop in this function, instead of the one in start_lex,
**	allowing us to skip nested expansions, or more simply put, the presence of
**	the `(' and `{' characters in the token. Otherwise (`$' and ``' notation),
**	we just check if we stumbled onto the start of another token, or if we
**	found the matching backquote.
**
**	Example:			$( foo (bar))
**							       ^
**				  This one isnt closing the token, but its the
**				  first closing bracket.
*/

static int	close_expand(t_lexer *lex, char open, char close)
{
	int	stack;

	stack = 1;
	while (lex->line[lex->index] && stack != 0)
	{
		if (charcmp(lex->line, lex->index, open))
			stack++;
		else if (charcmp(lex->line, lex->index, close))
			stack--;
		lex->index++;
	}
	return (1);
}

/*
**	After token_start, the index is on the character following the the ``' or
**	the `$'.
*/

int			match_expand(t_lexer *lex, size_t token_start)
{
	if (lex->line[token_start] == '`')
	{
		if (charcmp(lex->line, lex->index, '`'))
		{
			lex->index++;
			return (1);
		}
	}
	else if (lex->line[token_start] == '$')
	{
		if (charcmp(lex->line, lex->index, '('))
			return (close_expand(lex, '(', ')'));
		else if (charcmp(lex->line, lex->index, '{'))
			return (close_expand(lex, '{', '}'));
		else
		{
			if (IS_INPUT_END(lex->line[lex->index]) || \
					IS_WHITESPACE(lex->line[lex->index]))
				return (1);
		}
	}
	return (0);
}
