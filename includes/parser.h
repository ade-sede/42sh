/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:42:10 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/11 22:42:13 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "t_ast.h"
# include "lexer.h"

# define PARSER_ERROR 1
# define PARSER_SUCCESS 0

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
**	In file srcs/parser/parse.c
*/

int			ast_parse(t_ast **ast, t_lst_head **head, t_list **token_list);

/*
**	In file srcs/parser/parse_complexe_command.c
*/

t_ast		*start_complexe_command(t_ast *ast, t_list **token_list,
		int *reopen);

/*
**	In file srcs/parser/parse_pipe.c
*/

void		add_last_pipe(t_lst_head **head);
int			add_pipe(t_token *token, t_lst_head **head);

/*
**	In file srcs/parser/parse_redir.c
*/

t_ast		*append_redir(t_ast *root, t_token *token, t_list **token_list);

/*
**	In file srcs/parser/parse_simple_command.c
*/

t_ast		*create_simple_command(t_list **token_list);
t_ast		*fill_simple_command(t_ast *simple_cmd, t_list **token_list);
void		read_tree(t_ast *ast_start);
t_ast		*complete_complexe_command(t_ast *ast, t_list **token_list,
		int *reopen);

#endif
