/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */ /*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 13:29:27 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/08 20:22:23 by ade-sede         ###   ########.fr       */
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
**			The function stops, and stack goes back to ast_separator, bulding a
**			new branch for the new command, and attaching the simple command we
**			just created to a complexe one.
*/

t_ast	*ast_create_command(t_ast **root, t_list **token_list, int *command_name)
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
#ifdef PARSER_DEBUG
			printf("SEPARATOR\n"RESET);
#endif
			return (tmp_root);
		}
		else
		{
			if (TK_IS_REDIR(token->id))
			{
#ifdef PARSER_DEBUG
				printf("TK_REDIR\n"RESET);
#endif

				/* create new_node */
				new_node = ast_create_node_from_redir(token_list);
				ft_simple_lst_add(&tmp_root->child, ft_simple_lst_create(new_node));
			}
			else
			{
				new_node = ast_create_node_from_word(token_list, command_name);
				ft_simple_lst_pushback(&tmp_root->child, ft_simple_lst_create(new_node));
			}
			tmp_root = ast_create_command(root, token_list, command_name);
		}
	}
	return (tmp_root);
}

/*
**	Creates a node from a word token, returns it.
*/

t_ast	*ast_create_node_from_word(t_list **token_list, int *command_name)
{
	t_ast	*node;
	t_token	*token;

	token = (*token_list)->data;
	if ((token->id == TK_WORD || token->type == EXPAND) && *command_name == FALSE)
	{
		node = ast_create_node((*token_list)->data, NULL, CMD_NAME);
		*command_name = TRUE;
	}
	else
	{
		if (*command_name == FALSE)
			node = ast_create_node((*token_list)->data, NULL, CMD_PREFIX);
		else
			node = ast_create_node((*token_list)->data, NULL, CMD_SUFFIX);
	}
	ft_simple_lst_del_one(token_list, *token_list, NULL);
	return (node);
}
