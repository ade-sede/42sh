/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:37 by ade-sede          #+#    #+#             */
/*   Updated: 2018/05/25 20:43:38 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

static int	check_prev_1(t_lexer *lex)
{
	t_token	*token;
	t_list	*node;

	token = NULL;
	node = NULL;
	node = lex->reversed_list;
	if (!node)
		return (FALSE);
	token = node->data;
	if (token->id == TK_NEWLINE)
	{
		return (TRUE);
	}
	if (IS_RESERVED_WORD(token->id) && token->id != TK_FOR \
			&& token->id != TK_CASE && token->id != TK_IN)
		return (TRUE);
	return (FALSE);
}

static int	check_prev_3(t_lexer *lex)
{
	t_token	*token;
	t_list	*node;

	token = NULL;
	node = NULL;
	node = lex->reversed_list;
	while (node)
	{
		token = node->data;
		if (token->id != TK_NEWLINE)
			break ;
		node = node->next;
	}
	node = ft_simple_lst_get_n(node, 1);
	if (!node)
		return (FALSE);
	token = node->data;
	if (token->id == TK_FOR || token->id == TK_CASE)
		return (TRUE);
	return (FALSE);
}

static int	check_for(t_lexer *lex, const char *value)
{
	t_token	*token;

	if (!lex->reversed_list)
		return (FALSE);
	token = lex->reversed_list->data;
	if (token->id != TK_FOR)
		return (FALSE);
	if (!check_valid_name(value, ft_strlen(value)))
		return (FALSE);
	return (TRUE);
}

/*
**	Need to apply a special rule so that word() lets ( and ) be recogniszed
**	as reserved words even if cmd_name is closed.
*/

int			id_word(t_lexer *lex, t_token *token)
{
	t_token	*func_name_token;
	int		id;

	if ((func_name_token = check_function_name(lex, token->value)))
		func_name_token->id = TK_NAME;
	if (check_io_number(token))
		id = TK_IO_NUMBER;
	else if (check_assignement_word(lex, token->value))
		id = TK_ASSIGNMENT_WORD;
	else if (check_prev_1(lex))
		id = id_reserved_words(token->value);
	else if (check_prev_3(lex))
		id = id_reserved_words(token->value);
	else if (check_for(lex, token->value))
		id = TK_NAME;
	else if (lex->cmd_name_open || ft_strequ("(", token->value) \
			|| ft_strequ(")", token->value))
		id = id_reserved_words(token->value);
	else
		id = TK_WORD;
	return (id);
}
