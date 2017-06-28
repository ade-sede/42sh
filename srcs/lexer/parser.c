/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 13:34:01 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/28 15:41:08 by ade-sede         ###   ########.fr       */
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
**	from its leafs to its root. The `parent' argument, is the current highest
**	node of the branch we are building. The very first parent node is an empty
**	node created by the function called ast_process_token(). The function will
**	return the node that is considered to be the highest parent of the tree
**	(new_parent), and after the last token has been parsed into the tree, this
**	highest node should be the root node.  We can highlight two different
**	behaviors determining the value of the new_parent node:
**	- If the command is a simple_command, new_parent should be the parent given as
**	an argument.
**	- If the command is a complexe_command (one with separators, or a
**	pipeline), the node new_parent will be a new node, wich has as a first
**	child argument `parent'.
**	Consider the command ls | cat -e:
**
**		When parsing the token `ls':
**		- The `parent' node is the initial node created by the caller.
**		- We create a node containing a CMD_NAME
**		(WORD `ls'), wich is the child of our parent node.
**		- We return `new_parent' = `parent'.
**		
**		When parsing the token `|':
**		- The `parent' node is the one originaly created by the caller,
**		returned when parsing the token `ls'.
**		- We create a new node,
*/

t_ast	*ast_process_token(t_ast *parent, t_token *token)
{
	t_ast	*new_parent = NULL;
	t_ast	*new_node = NULL;

	(void)new_node;
	(void)parent;
	(void)token;
	return (new_parent);
}
