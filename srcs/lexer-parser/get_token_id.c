/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_id.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 15:10:18 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/29 12:10:13 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

/*
**	Work in progress
*/

/*
**	Trying to determine the ID of the token using its context (delimiter, lexer
**	state).
*/

t_token_id		get_token_id(t_token *token, char delimiter)
{
	t_token_id	id;
	int			done;

	done = FALSE;
	id = -1;
	if (token->type == OPERATOR)
		id = lex_id_operator(token->value);
	else if (token->type == WORD)
	{
		if (!done)
			done = lex_id_io_number(token, delimiter, &id);
		if (!done)
			done = lex_id_word(token, &id);
	}
	return (id);
}
