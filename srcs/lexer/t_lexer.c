/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:50 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:22 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_lexer.h"
#include "token.h"
#include "libft.h"

/*
**	Initializes the lexer with default value.
*/

t_lexer		init_lexer(const char *line)
{
	t_lexer		lex;

	lex.line = ft_strdup(line);
	lex.index = 0;
	lex.stack = NULL;
	lex.reopen = 1;
	lex.state = DEFAULT;
	lex.last_id = TK_WORD;
	return (lex);
}
