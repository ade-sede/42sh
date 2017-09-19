/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:46 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:05:59 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
# include "token.h"

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
**	In file srcs/parser/t_ast.c
*/

t_ast				*ast_create_node(t_token *token, t_list *child, \
		t_symbol symbol);
t_ast				*free_ast_node(t_ast *node);
t_ast				*flush_tree(t_ast *ast);
#endif
