/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 18:16:43 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/01 19:19:47 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"


t_lexer	*tokenize(const char *line)
{
	t_lexer		lex;
	size_t		token_start_index;
	int			done;
	t_lexer_state state;

	lex = init_lexer(line);
	done = 0;
	while (lex.line[lex.index])
	{
		if (!done)
			state = lex.state;
		if (!done && lex.state != DQUOTE && lex.state != QUOTE && (done = token_start(lex)))
			token_start_index = lex.index;
		if (lex.state != DQUOTE && lex.state != QUOTE && token_start(lex))
		{
			push_token(lex, token_start_index);
			//identify_token;
		}
		sate = lex.state;
		lex.state = update_state(lex);
		lex.index++;
	}
}

int		push_token(t_lexer lex, size_t token_start)
{
	char	*value;
	t_token	*token;
	t_list	*node;

	value = ft_strsub(lex.line, token_start, lex.index - token_start);
	token = create_token(value, lex.state);
	node = ft_simple_lst_create(token);
	ft_simple_lst_add(&lex.stack, node);
	return (1);
}

int		token_start(t_lexer lex)
{
	if (lex.index == 0 && lex.stack == NULL)
		return (1);
}

int		update_state(t_lexer lex)
{
	if ()
}
