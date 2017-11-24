/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:37 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:37 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "syntax_coloring.h"
#include "libft.h"

int		lex_action_comment_le(t_lexer *lex, struct s_info **state_info, \
		t_line *line)
{
	if (lex->line[lex->pos] == 0)
		pop_state_le(lex, state_info);
	else if (lex->line[lex->pos] == '\n')
	{
		consume_input_le(lex, line);
		pop_state_le(lex, state_info);
	}
	else
		consume_input_le(lex, line);
	return (TRUE);
}
