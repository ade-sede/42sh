/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 11:35:32 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 12:14:12 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_coloring.h"
#include "libft.h"

int	loop_le_delim(t_lexer *lex, t_line *line)
{
	while (lex->line[lex->pos] && delim(lex, line))
		;
	return (((struct s_info*)lex->state->data)->state);
}
