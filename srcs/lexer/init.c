/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 18:23:00 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/28 13:42:55 by ade-sede         ###   ########.fr       */
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

	lex.line = line;
	lex.index = 0;
	lex.stack = NULL;
	lex.state = DEFAULT;
	return (lex);
}

/*
**	Creates a token, storing the string value, its type and the value's lenght.
*/

t_token		*create_token(char *value, t_token_type type)
{
	t_token		*token;

	token = palloc(sizeof(*token));
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

t_ast		*create_ast_node(t_list	*child, t_token *token)
{
	t_ast	*node;

	node = palloc(sizeof(*node));
	node->child = child;
	node->token = token;
	return (node);
}
