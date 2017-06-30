/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 13:29:27 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/30 21:42:43 by ade-sede         ###   ########.fr       */
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
**	not hold a token. The function ast_create_command takes the full list of tokens,
**	and a temporary root to build upon. This temporary root is considered to be
**	a `simple command'.
** 	The function will create a node, that will act as a temporary root for our
** 	tree. For each token it reads from the list:
**	- If the token is a WORD (not an operator ?)
**		
**		A node will be created from that token by the function ast_create_node_from_word. The
**		node's symbol should be determined according to the POSIX STANDARD's
**		rules. This node will then be appended to the child list of the current
**		root node.
**
**	- If the token is an operator
**		- If the token is a redirection / an IO_NUMBER
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
**			by a call to ast_create_command with the remaining tokens, and a child of
**			the new root as a temporary root.
*/

t_ast	*ast_create_command(t_ast **root, t_list **token_list)
{
	t_ast	*tmp_root;
	t_ast	*new_node;
	t_token	*token;

	tmp_root = *root;
	if (*token_list)
	{
		token = (*token_list)->data;
		if (token->id == TK_WORD)
		{
			new_node = ast_create_node_from_word(token_list);
			ft_simple_lst_pushback(&tmp_root->child, ft_simple_lst_create(new_node));
			tmp_root = ast_create_command(root, &(*token_list)->next);
		}
	}
	return (tmp_root);
}

t_ast	*ast_create_node_from_word(t_list **token_list)
{
	t_ast	*node;

	node = ast_create_node((*token_list)->data, NULL, 0);
	/*	ASSIGN THE RIGHT SYMBOL */
	*token_list = (*token_list)->next;
	return (node);
}
