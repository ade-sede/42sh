/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_id.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 15:10:18 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/05 16:37:30 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

/*
**	Trying to determine the ID of the token using its context (delimiter, lexer
**	state).
*/

t_token_id		get_token_id(t_token *token, char delimiter)
{
	t_token_id	id;

	id = -1;
	(void)delimiter;
	if (token->type == OPERATOR)
		match_operator(token->value, 0, token->size, &id);
	else if (token->type == WORD)
		id_io_number(token, delimiter, &id);
	return (id);
}
