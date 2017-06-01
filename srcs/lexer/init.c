/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 18:23:00 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/01 19:18:23 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

t_lexer		init_lexer(const char *line)
{
	t_lexer		lex;

	lex.line = line;
	lex.index = 0;
	lex.stack = NULL;
	lex.state = IN_NONE;
	return (lex);
}

t_token		*create_token(char *line, int token_type)
{
	t_token		*token;

	token = palloc(sizeof(*token));
	token->value = line;
	token->type = token_type;
	token->size = ft_strlen(line);
}
