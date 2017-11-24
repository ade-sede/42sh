/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 20:41:16 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/23 20:50:21 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin.h"
#include "lexer.h"

static int	perform_subsitution(t_lexer *lex, t_list *alias_node, \
		t_list **alias_copy, t_list **token_list)
{
	char	*alias_value;
	ssize_t	eq_index;
	t_lexer new_lex;
	size_t	ret;

	alias_value = alias_node->data;
	ft_simple_lst_del_one(alias_copy, alias_node, NULL);
	eq_index = ft_strichr(alias_value, '=');
	init_lexer(&new_lex, alias_value + eq_index + 1);
	ret = get_token_list(&new_lex, token_list, *alias_copy);
	ft_simple_lst_remove(&lex->state_list, free_info);
	lex->state_list = new_lex.state_list;
	new_lex.state_list = NULL;
	lex->state = new_lex.state;
	lex->cmd_name_open = new_lex.cmd_name_open;
	ft_simple_lst_pushback(&new_lex.reversed_list, lex->reversed_list);
	lex->reversed_list = new_lex.reversed_list;
	new_lex.reversed_list = NULL;
	free_lexer(&new_lex);
	return (ret);
}

t_list		*expand_alias(t_lexer *lex, t_token **token, t_list *alias_list)
{
	t_list	*alias_node;
	t_list	*alias_copy;
	t_list	*token_list;
	int		ret;

	alias_copy = NULL;
	token_list = NULL;
	if ((*token)->cmd_name == FALSE || !alias_list)
		return (NULL);
	ft_simple_lst_dup(&alias_copy, alias_list);
	if ((alias_node = find_alias(alias_copy, (*token)->value, \
					ft_strlen((*token)->value))) != NULL)
		ret = perform_subsitution(lex, alias_node, &alias_copy, &token_list);
	else
	{
		ft_simple_lst_remove(&alias_copy, NULL);
		return (NULL);
	}
	ft_simple_lst_remove(&alias_copy, NULL);
	if (token_list || (!token_list && ret == LEXER_REOPEN))
	{
		free_token(*token);
		*token = NULL;
	}
	return (token_list);
}
