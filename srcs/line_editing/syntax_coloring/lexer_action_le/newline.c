/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 20:09:43 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 12:34:58 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "syntax_coloring.h"
#include "libft.h"

int		lex_action_newline_le(t_lexer *lex, struct s_info **state_info, \
		t_line *line)
{
	consume_input_le(lex, line);
	pop_state_le(lex, state_info);
	return (TRUE);
}
