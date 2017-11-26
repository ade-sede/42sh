/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:37 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:28 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"

static char	*g_operator_list[] =
{
	"<",
	"<<",
	">",
	";",
	"|",
	"&",
	"&&",
	"||",
	";;",
	"<<",
	">>",
	"<&",
	">&",
	"<>",
	"<<-",
	">|",
	NULL
};

int		lex_action_operator(t_lexer *lex, struct s_info **state_info)
{
	t_word			operator_string;
	struct s_info	*info;
	size_t			i;

	i = 0;
	info = lex->state->data;
	if (lex->line[lex->pos] == 0)
	{
		pop_state(lex, state_info);
		return (TRUE);
	}
	w_newword(&operator_string);
	if (info->value.str)
		w_addstr(&operator_string, info->value.str);
	w_addchar(&operator_string, lex->line[lex->pos]);
	while (g_operator_list[i] && !ft_strequ(g_operator_list[i],\
				operator_string.str))
		++i;
	if (g_operator_list[i])
		consume_input(lex);
	else
		pop_state(lex, state_info);
	w_free(&operator_string);
	return (TRUE);
}
