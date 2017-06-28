/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 13:34:01 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/28 19:12:54 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "libft.h"

/*
**	NOTE TO SELF:
**
**	Commands need to be considered as nodes in order for the tree to be
**	complete.
*/

/*
**	As a token is considered to be a leaf of the tree, the tree is being built
**	from the leaves to the root. Upon reading, tokens are converted into the
**	AST's nodes. Some nodes merely represent a symbol from our grammar, and do
**	not hold a token. The function CREATE_AST takes the full list of tokens,
**	and a temporary root to build upon.
**
** 	The function will create a node, that will act as a temporary root for our
** 	tree. For each token it reads from the list:
**	- If the token is a WORD (not an operator ?)
**		
**		A node will be created from that token by the function NODE_FROM_WORD. The
**		node's symbol should be determined according to the POSIX STANDARD's
**		rules. This node will then be appended to the child list of the current
**		root node.
**
**	- If the token is an operator
**		- If the token is a redirection / and IO_NUMBER
**
**			A node representing an IO_REDIRECT should be created from every
**			token belonging to the redirection. This node will not hold any
**			token and will then be appended to the child list of the
**			current root node.
**
**		- If the token is a separator
**
**			A node representing the separator will be created from that token.
**			This token will be used as the new temporary root, and the old root
**			will become its child. The new root would be created recursively,
**			by a call to CREATE_AST with the remaining tokens, and a child of
**			the new root as a temporary root.
**
**
*/



t_ast	*CREATE_AST(t_ast **root, t_list *token_list)
{
	return (*root);
}

t_ast	*NODE_FROM_WORD(t_list **token)
{
	t_ast	*node;

	return (node);
}
