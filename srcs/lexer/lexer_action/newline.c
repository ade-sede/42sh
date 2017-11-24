/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 20:09:43 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/23 20:09:44 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

int		lex_action_newline(t_lexer *lex, struct s_info **state_info)
{
	consume_input(lex);
	pop_state(lex, state_info);
	return (TRUE);
}
