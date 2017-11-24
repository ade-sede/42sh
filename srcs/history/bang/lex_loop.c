/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 19:14:54 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 19:14:55 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "bang.h"
#include "lexer.h"

void	lex_loop(const char *source, t_list **list)
{
	t_lexer lex;
	t_list	*reversed_node;
	t_list	*node;
	t_token	*token;

	init_lexer(&lex, source);
	while (lex.line[lex.pos] && (token = get_token(&lex)))
	{
		if (token->state_info->state == COMMENT \
				|| token->state_info->state == WHITESPACE)
			free_token(token);
		else
		{
			node = ft_simple_lst_create(token);
			reversed_node = ft_simple_lst_create(token);
			ft_simple_lst_add(&lex.reversed_list, reversed_node);
			ft_simple_lst_pushback(list, node);
		}
	}
	free_lexer(&lex);
}
