/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 15:25:00 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/23 17:55:35 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
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
	lex.state = DEFAULT;
	return (lex);
}

/*
**	Creates a token, storing the string value, its type and the value's lenght.
*/

t_token		*create_token(char *value, t_token_type type, char delimiter)
{
	t_token		*token;

	token = palloc(sizeof(*token));
	token->delimiter = delimiter;
	token->value = value;
	token->id = 0;
	token->type = type;
	token->size = ft_strlen(value);
	return (token);
}

/*
**	Creates a node of the AST, giving the address of the first child of its
**	list of childs.
*/

t_ast		*ast_create_node(t_token *token, t_list *child, t_symbol symbol)
{
	t_ast	*node;

	node = palloc(sizeof(*node));
	node->child = child;
	node->token = token;
	node->symbol = symbol;
	return (node);
}
