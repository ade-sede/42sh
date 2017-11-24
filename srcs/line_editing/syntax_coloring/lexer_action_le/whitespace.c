/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whitespace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 20:11:41 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 12:36:31 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "syntax_coloring.h"
#include "libft.h"

int		lex_action_whitespace_le(t_lexer *lex, struct s_info **state_info, \
		t_line *line)
{
	if (lex->line[lex->pos] == ' ' || lex->line[lex->pos] == '\t')
		consume_input_le(lex, line);
	else
		pop_state_le(lex, state_info);
	return (TRUE);
}
