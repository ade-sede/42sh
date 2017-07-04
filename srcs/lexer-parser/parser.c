/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 13:29:27 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/04 18:44:53 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "color.h"
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
#ifdef PARSER_DEBUG
	printf(CYN"------------------------------------------------\n"RESET);
	printf("Addr of "BLU"token_list"RESET" && "MAG"*token_list"RESET" == "BLU"%p"RESET"  && "MAG"%p\n"RESET, token_list, *token_list);
#endif
	if (token_list && *token_list)
	{
		token = (*token_list)->data;
#ifdef PARSER_DEBUG
		printf("Treating token "MAG"#"CYN"%s"MAG"#\n"RESET, token->value);//			REMOVE		
		printf("Token has id : "YEL);
#endif
		if (TK_IS_SEP(token->id))
		{
			tmp_root = ast_separator(tmp_root, token_list);
		}
		else
		{
			if (token->id == TK_WORD)
			{
#ifdef PARSER_DEBUG
				printf("TK_WORD\n"RESET);
#endif
				new_node = ast_create_node_from_word(token_list);
				ft_simple_lst_pushback(&tmp_root->child, ft_simple_lst_create(new_node));
			}
			if (TK_IS_REDIR(token->id))
			{
#ifdef PARSER_DEBUG
				printf("TK_REDIR\n"RESET);
#endif
				/* create new_node */
				new_node = ast_create_node_from_redir(token_list);
				ft_simple_lst_add(&tmp_root->child, ft_simple_lst_create(new_node));
			}
			tmp_root = ast_create_command(root, token_list);
		}
	}
	return (tmp_root);
}

t_ast	*ast_separator(t_ast *current_tmp_root, t_list **token_list)
{
	t_ast	*new_root;
	t_ast	*node;
	t_list	*child_list;

	child_list = NULL;
	child_list = ft_simple_lst_create(current_tmp_root);
	node = ast_create_node(NULL, NULL, SIMPLE_COMMAND);
	ft_simple_lst_pushback(&child_list, ft_simple_lst_create(node));
	new_root = ast_create_node((*token_list)->data, child_list, PIPELINE);
	ft_simple_lst_del_one(token_list, *token_list, NULL);
	return (new_root);
}

/*
**	Creates a node from a word token, returns it.
*/

t_ast	*ast_create_node_from_word(t_list **token_list)
{
	t_ast	*node;

	node = ast_create_node((*token_list)->data, NULL, 0);
	ft_simple_lst_del_one(token_list, *token_list, NULL);
	/*	ASSIGN THE RIGHT SYMBOL */
	return (node);
}

/*
**	Creates an IO_REDIR node from 2 or 3 tokens. Returns this IO_REDIR node,
**	wich should be appended at the start of the command's child list.
**	The flag expected corresponds to what token the next part of the
**	redirection should be according to the one we just read.
**	1 = NAME
**	2 = REDIR
*/

t_ast	*ast_create_node_from_redir(t_list **token_list)
{
	t_list	*child_list;
	t_ast	*node;
	t_token	*token;
	int		expected;

	child_list = NULL;
	token = (*token_list)->data;
	if (token->id == TK_IO_NUMBER)
		expected = 2;
	else
		expected = 1;
	ft_simple_lst_pushback(&child_list, ft_simple_lst_create(ast_create_node(token, NULL, CMD_SUFFIX)));
	ft_simple_lst_del_one(token_list, *token_list, NULL);
	while (expected != 0)
	{
		token = (*token_list)->data;
		if (expected == 2)
		{
			/* Raise an error if the token is not a redir operator */
			ft_simple_lst_pushback(&child_list, ft_simple_lst_create(ast_create_node(token, NULL, CMD_SUFFIX)));
		}
		if (expected == 1)
		{
			/* Raise an error if the token is not a valid filename */
			ft_simple_lst_pushback(&child_list, ft_simple_lst_create(ast_create_node(token, NULL, CMD_SUFFIX)));
		}
		ft_simple_lst_del_one(token_list, *token_list, NULL);
		--expected;
	}
	node = ast_create_node(NULL, child_list, IO_REDIRECT);
	t_ast	*tmp_node;
	tmp_node= node->child->data;
	token = tmp_node->token;
	printf("%s\n", token->value);//			REMOVE		
	return (node);
}
