/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_id.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 05:07:29 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 05:08:29 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

/*
**	Trying to determine the ID of the token using its context (delimiter, lexer
**	state). This id will be used by the parser to help assign grammar symbol to
**	the token and build the tree.
*/

t_token_id		lex_get_token_id(t_token *token)
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
			done = lex_id_io_number(token, token->delimiter, &id);
		if (!done)
			done = lex_id_word(token, &id);
	}
	else if (token->type == DQUOTED || token->type == QUOTED)
		id = TK_WORD;
	return (id);
}
