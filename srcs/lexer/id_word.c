/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_word.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 16:20:49 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/05 16:31:51 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

/*
**	When trying to get the token id, if the token is a WORD, it might be an
**	IO_NUMBER.  Checking here.
*/

int		id_io_number(t_token *token, char delimiter, t_token_id *id)
{
	size_t	i;
	
	i = 0;
	if (delimiter != '<' && delimiter != '>')
		return (0);
	while (token->value[i] && ft_isdigit(token->value[i]))
		i++;
	if ((token->value[i]))
		return (0);
	*id = TK_IO_NUMBER;
	return (1);
}
