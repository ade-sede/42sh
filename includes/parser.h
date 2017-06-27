/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 18:34:30 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/27 19:16:17 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"

/*
**	After a token is delimited, it is sent to the parser, wich will build an
**	AST (abstract syntax tree) from the stream of token it receives.
**	The leafs of the tree should be the delimited tokens, and their parents
**	should be the grammar symbol representing them, and the very top node of
**	the tree (the root node) should not contain any token, only a list of
**	childs.
*/

/*
**	Matching tokens to grammar symbol according to the context is done
**	according to the POSIX STANDARD found here:
**	http://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html
*/

/*
**	The following structure represents a node of the AST.
**	The node should contain the token it has been created from, and a list of
**	its child such that child->data is a t_ast structure.
**	As an example consider the command "ls foo bar":
**	- The root node has one child : the command name "ls".
**	- The command name ls has 2 childs : the word "foo", and the word "bar".
*/

typedef	struct	s_ast
{
	t_list		*child;
	t_token		*token;
}				t_ast;

/*
**	The tree should be read from the root nodes, in a left-recursive order.
**	Meaning the next node is treated only after the current one has been
**	solved. So that prioritary operations are executed first, they are always
**	pushed to the left of the tree (wich is the start of the child list).
*/
#endif
