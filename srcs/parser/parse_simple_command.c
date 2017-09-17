/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_simple_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 23:16:26 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/17 17:10:05 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"
#include "lexer.h"
#include "parser.h"
#include "color.h"
#include "libft.h"
#include "exec.h"
#include "printf.h"

/*
**	If we have an assignement work token, such as key=value, where value is
**	contained in another token, we join the two tokens.
**	Example:
**
**	`key="value"' is a valid assignement. token 1 has value `key=' and token 2
**	and unquoted `value' (quote removal already occured).
**
**	`key= "value"' is not a valid assignement.
**	We are doing this only and only if the assignement isnt complete, and the
**	character following the first equal sign in token1 is null.
*/

static void	complete_assignement_word(t_list **token_list)
{
	t_token	*token;
	t_token	*next_token;
	char	*eq_sign;

	eq_sign = NULL;
	token = (*token_list)->data;
	eq_sign = ft_strchr(token->value, '=');
	if (*(eq_sign + 1) == 0 && (*token_list)->next)
	{
		next_token = (*token_list)->next->data;
		if (next_token->type == DQUOTED || next_token->type == QUOTED)
		{
			next_token = (*token_list)->next->data;
			token->value = ft_strchange(token->value, \
					ft_strjoin(token->value, next_token->value));
			ft_simple_lst_del_one(token_list, (*token_list)->next, free_token);
		}
	}
}

/*
**	Creates a node from a word token, returns it.
*/

t_ast		*ast_create_node_from_word(t_list **token_list)
{
	t_ast	*node;
	t_token	*token;

	token = (*token_list)->data;
	if (token->id == TK_ASSIGNMENT_WORD && \
			(token->delimiter == '"' || token->delimiter == 39))
		complete_assignement_word(token_list);
	if ((token->id == TK_WORD || token->type == EXPAND) \
			&& token->cmd_name)
		node = ast_create_node((*token_list)->data, NULL, CMD_NAME);
	else
	{
		if (token->cmd_name)
			node = ast_create_node((*token_list)->data, NULL, CMD_PREFIX);
		else
			node = ast_create_node((*token_list)->data, NULL, CMD_SUFFIX);
	}
	ft_simple_lst_del_one(token_list, *token_list, NULL);
	return (node);
}

t_ast		*create_simple_command(t_list **token_list)
{
	t_ast	*ast;

	ast = ast_create_node(NULL, NULL, SIMPLE_COMMAND);
	ast = fill_simple_command(ast, token_list);
	return (ast);
}

t_ast		*fill_simple_command(t_ast *simple_cmd, t_list **token_list)
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
