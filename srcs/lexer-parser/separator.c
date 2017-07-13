/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 12:58:22 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/13 16:42:27 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "parser.h"

static void	start_simple_command(t_ast **root, t_list **token_list, \
		int *command_name)
{
	*root = ast_create_node(NULL, NULL, SIMPLE_COMMAND);
	*root = ast_create_command(root, token_list, command_name);
	*command_name = 0;
}

static void	start_complexe_command(t_ast **root, t_list **token_list, \
		int *command_name, t_token *token)
{
	t_ast	*new_branch_root;
	t_list	*child;

	child = ft_simple_lst_create(*root);
	new_branch_root = ast_create_node(NULL, NULL, SIMPLE_COMMAND);
	ft_simple_lst_pushback(&child, ft_simple_lst_create(new_branch_root));
	*root = ast_create_node(token, child, COMPLEXE_COMMAND);
	ft_simple_lst_del_one(token_list, *token_list, NULL);
	new_branch_root = ast_create_command(&new_branch_root, \
			token_list, command_name);
	*command_name = 0;
}

t_ast		*ast_separator(t_ast **root, t_list **token_list)
{
	int		command_name;
	t_token *token;

	command_name = 0;
	if (token_list && *token_list)
	{
		token = (*token_list)->data;
		if (TK_IS_SEP(token->id))
			start_complexe_command(root, token_list, &command_name, token);
		else
			start_simple_command(root, token_list, &command_name);
		if (token_list && *token_list)
			ast_separator(root, token_list);
	}
	return (*root);
}
