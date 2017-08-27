/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 05:08:19 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 05:08:21 by vcombey          ###   ########.fr       */
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
**	In some situations, the parser should expect a particular symbol to fit the
**	current tree. Meaning the next token will be considered (if possible) as
**	the particular symbol we were expecting. Otherwise we'll raise an error.
**	Condiser a command includes an redirection operation:
**
**		After a redirection operator, the parser needs a filename to complete
**		an IO_file symbol. So the next token needs to be a WORD, indentifiable
**		as an unix case filename. If it is not, we raise a parse error.
*/

/*
** 		IMPLICIT SYMBOLS
**
** 	The root node is implicitely considered as a command (That can itself be
** 	composed of other commands, or not).
**	Consider the following command : ls > foo.
**	A representation of the tree would be :
**
**				|	 |						|
**				|ROOT|						|	The root node, linking all
**				|____|						|	commands.
**			 ____|	|____					;
**			|			|					|
**		CMD_NAME	CMD_SUFFIX				|	At this stage, we have a
**		WORD ('ls')		|					|	simple command, that we
**		 				|					;	can access from the root.
**		 			IO_REDIRECT				|
**		 				|					|
**		 				|					|
**		 			IO_FILE					|
**		 			|	  |					|
**				OP('>')	FILENAME
**						WORD ('foo')
**
** 	We see that there is no branching from the node CMD_SUFFIX to the node
** 	IO_FILE. There is no point in keeping 'useless' nodes in the tree. This can
** 	also be explained by the recursive nature of the tree.We will prefer the
** 	absolutly equivalent tree:
**
**			|	 |
**			|ROOT|
**			|____|
**		 ____|	|____
**		|			|
**	CMD_NAME	IO_FILE
**  WORD ('ls')	|	  |
**          OP('>') FILENAME
**              	WORD ('foo')
**
**	NOTE: In the 2 last tree, the redirection operations should actually be
**	placed on the left of the tree, to make sure it happens at the right
**	moment.
**
**		READING:
**
**	The tree should be read from the root nodes, in a left-recursive order.
**	Meaning the next node is treated only after the current one has been
**	solved. So that prioritary operations are executed first, they are always
**	pushed to the left of the tree (wich is the start of the child list).
*/

/*
**	The following enumeration corresponds to different grammar symbols we'll be
**	using in our tree. It is a simplified version of the one found on the POSIX
**	STANDARD Each node of our AST will correspond to one of those.
**	symbols.
*/

/*
**	CMD_WORD applies to any word belonging to a command.
*/

typedef	enum {
	SIMPLE_COMMAND,
	IO_REDIRECT,
	COMPLEXE_COMMAND = 666,
	CMD_WORD = 999,
	CMD_NAME,
	CMD_PREFIX,
	CMD_SUFFIX
}	t_symbol;

/*
**	The following structure represents a node of the AST.
**	The node should contain the token it has been created from, and a list of
**	its child such that child->data is a t_ast structure.
**	As an example consider the command "ls foo bar":
**
**		The root node is considered to be a command. Its childs are the
**		CMD_NAME `ls', and the CMD_PREFIX `foo bar' ,itself composed of
**		CMD_PREFIX `foo' and CMD_PREFIX `bar' (see IMPLICIT SYMBOLS).
*/

typedef	struct		s_ast
{
	t_list			*child;
	struct s_token	*token;
	t_symbol		symbol;
}					t_ast;

/*
**	In file parser.c
*/

t_ast				*ast_parse(t_ast **root, t_list **token_list);
t_ast				*ast_create_simple_command(t_ast **root, \
		t_list **token_list, int *command_name);

/*
**	In file casual_node.c
*/

t_ast				*ast_create_node_from_word(t_list **token_list, \
		int *command_name);

/*
**	In file redir.c
*/

t_ast				*ast_create_node_from_redir(t_list **token_list);

/*
**	In file init.c
*/

t_ast				*ast_create_node(struct s_token *token, t_list *child, \
		t_symbol symbol);
#endif
