/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whitespace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 20:11:41 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/23 20:12:01 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

int		lex_action_whitespace(t_lexer *lex, struct s_info **state_info)
{
	if (lex->line[lex->pos] == ' ' || lex->line[lex->pos] == '\t')
		consume_input(lex);
	else
		pop_state(lex, state_info);
	return (TRUE);
}
