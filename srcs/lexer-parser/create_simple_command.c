/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_simple_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 23:16:26 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/15 23:54:28 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"
#include "lexer.h"
#include "parser.h"
#include "color.h"
#include "libft.h"
#include "exec.h"
#include "printf.h"

t_ast			*create_simple_command(t_list **token_list)
{
	t_ast	*ast;

	ast = ast_create_node(NULL, NULL, SIMPLE_COMMAND);
	ast = fill_simple_command(ast, token_list);
	return (ast);
}

t_ast			*fill_simple_command(t_ast *simple_cmd, t_list **token_list)
{
	t_ast	*new_node;
	t_token	*token;

	if (token_list && *token_list)
	{
		token = (*token_list)->data;
		if (TK_IS_SEP(token->id))
			return (simple_cmd);
		else
		{
			if (TK_IS_REDIR(token->id))
			{
				if (!(simple_cmd = append_redir(simple_cmd, token_list)))
					return (NULL);
			}
			else
			{
				new_node = ast_create_node_from_word(token_list);
				ft_simple_lst_pushback(&((simple_cmd)->child), \
						ft_simple_lst_create(new_node));
			}
			simple_cmd = fill_simple_command(simple_cmd, token_list);
		}
	}
	return (simple_cmd);
}
