/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 18:16:43 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/03 00:37:27 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <stdio.h>

/*
**	We are reading our input line 1 char a time, looking for the delimiter of
**	our token. Everytime we're done matching a token, we reset our token_start
**	wich gives us the index of the first char of the token.
**
**	If the character we are currently reading completes the match :
**	-	Create a token from what we just read.
**	-	Assign an id (type ?) to the token.
**	-	Push this token onto the stack (here adding it at the start of the list).
*/


/*
**	To determine the id of a token we used the state we were in when we were
**	reading the token.
*/

int	start_lex(t_lexer *lex)
{
	size_t	token_start;
	size_t	token_end;

	token_start = 0;
	while (lex->line[lex->index])
	{
		token_start = lex->index;
		lex->state = update_state(lex);
		while (!(token_end = token_match(lex, token_start)))
			lex->index++;
		tokenize(lex, token_start, token_end);
	}
	return (1);
}

int		tokenize(t_lexer *lex, size_t token_start, size_t token_end)
{
	char	*value;
	t_token	*token;
	t_list	*node;

	value = ft_strsub(lex->line, token_start, token_end + 1 - token_start);
	token = create_token(value, lex->state);
	get_token_id(token);
	node = ft_simple_lst_create(token);
	if (lex->stack == NULL)
		lex->stack = node;
	else
		ft_simple_lst_add(&(lex->stack), node);
	return (1);
}


/*
**	Returns the new lexer state depending on the character we're reading and
**	the current state.
*/

int		update_state(t_lexer *lex)
{
	if (IS_QUOTED(lex->state))
	{
		if (IS_QUOTED(lex->line[lex->index]))
		{
			lex->index++;
			return (DEFAULT);
		}
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
	else if (IS_WHITESPACE(lex->line[lex->index]))
	{
		lex->index++;
		return (DEFAULT);
	}
	return (lex->state);
}

/*
**	DETERMINING WHERE A TOKEN START AND ENDS :
**	See POSIX STANDARDS @ Token Recognition (2.3)
**
**	The last char of the token we matched is either the one we are on, or the
**	one before depending on wether or not we were in a "contained" token.
**	Examples:			`ls .'
**						   ^		
**				When we reach this space, we have a match and line[index] == ' ';
**				The token "ls" ends at the char line[index - 1];
**
**			`"This is  a quoted string"ls'
**								      ^	
**			When we reach the `"' we have a match. The token ends on this char.
**	
**	The index of the last char included in the token should be returned by the
**	token_match() function.
**
**	In the second case, we want to increment index, so that index is
**	positioned on the first char of the new token in every case
*/

int		token_match(t_lexer *lex, size_t token_start)
{
	if (IS_INPUT_END(lex->line[lex->index]) && token_start + 1 != lex->index)
		return (lex->index - 1);
	else if (IS_QUOTED(lex->state) && charcmp(lex->line, lex->index, lex->state))
		return (lex->index++);
	else if (IS_WHITESPACE(lex->line[lex->index]) && token_start + 1 != lex->index)
		return (lex->index - 1);
	return (0);
}
