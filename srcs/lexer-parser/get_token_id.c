/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_id.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 22:41:02 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/15 22:41:13 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

/*
**	Trying to determine the ID of the token using its context (delimiter, lexer
**	state). This id will be used by the parser to help assign grammar symbol to
**	the token and build the tree.
*/

t_token_id		lex_get_token_id(t_lexer *lex, t_token *token)
{
	t_token_id	id;
	int			done;

	done = FALSE;
	id = -1;
	if (token->type == OPERATOR)
		id = lex_id_operator(token->value);
	else if (token->type == WORD)
	{
		if (ft_strequ(token->value, "\n"))
		{
			done = TRUE;
			id = TK_NEWLINE;
		}
		if (!done)
			done = lex_id_io_number(token, token->delimiter, &id);
		if (!done)
			done = lex_id_word(lex, token, &id);
	}
	else if (token->type == DQUOTED || token->type == QUOTED)
		id = TK_WORD;
	return (id);
}
