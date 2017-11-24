/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 20:10:46 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 12:36:21 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "syntax_coloring.h"
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

int		lex_action_operator_le(t_lexer *lex, struct s_info **state_info, \
		t_line *line)
{
	t_word			operator_string;
	struct s_info	*info;
	size_t			i;

	i = 0;
	info = lex->state->data;
	if (lex->line[lex->pos] == 0)
	{
		pop_state_le(lex, state_info);
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
		consume_input_le(lex, line);
	else
		pop_state_le(lex, state_info);
	w_free(&operator_string);
	return (TRUE);
}
