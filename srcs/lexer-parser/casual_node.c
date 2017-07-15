/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casual_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/14 17:40:08 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/14 17:40:48 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "libft.h"

/*
**	Creates a node from a word token, returns it.
*/

t_ast		*ast_create_node_from_word(t_list **token_list, int *command_name)
{
	t_ast	*node;
	t_token	*token;

	token = (*token_list)->data;
	if ((token->id == TK_WORD || token->type == EXPAND) \
			&& *command_name == FALSE)
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
