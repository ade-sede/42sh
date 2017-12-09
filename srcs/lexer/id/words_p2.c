/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_p2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:37 by ade-sede          #+#    #+#             */
/*   Updated: 2017/12/09 17:25:35 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

int			check_valid_name(const char *value, size_t size)
{
	size_t	i;

	i = 0;
	while (value[i] && size)
	{
		if (i == 0 && ft_isdigit(value[i]))
			return (FALSE);
		if (!ft_isalnum(value[i]) && value[i] != '_')
			return (FALSE);
		--size;
		++i;
	}
	return (TRUE);
}

t_token		*check_function_name(t_lexer *lex, const char *value)
{
	t_list	*node;
	t_token	*token;

	node = lex->reversed_list;
	if (!ft_strequ(value, ")") || !node)
		return (NULL);
	token = node->data;
	if (token->id != TK_LPAREN)
		return (NULL);
	node = node->next;
	if (!node)
		return (NULL);
	token = node->data;
	if (!check_valid_name(token->value, ft_strlen(token->value)))
		token = NULL;
	return (token);
}

int			check_assignement_word(t_lexer *lex, const char *value)
{
	int		i;
	int		in_exp;
	ssize_t	eq_index;

	i = 0;
	in_exp = -1;
	eq_index = -1;
	if (!lex->cmd_name_open)
		return (FALSE);
	while (value[i])
	{
		if (charcmp(value, i, '$'))
			in_exp = i;
		if (charcmp(value, i, '='))
			eq_index = i;
		++i;
	}
	if (eq_index == -1 || eq_index == 0 || (in_exp != -1 && in_exp < eq_index))
		return (FALSE);
	if (!check_valid_name(value, eq_index))
		return (FALSE);
	return (TRUE);
}

int			check_io_number(t_token *token)
{
	size_t	i;

	i = 0;
	if (token->delim != '<' && token->delim != '>')
		return (FALSE);
	while (token->value[i])
	{
		if (!ft_isdigit(token->value[i]))
			return (FALSE);
		++i;
	}
	return (TRUE);
}
