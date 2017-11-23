/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 19:32:53 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/23 20:39:51 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_lexer.h"
#include "t_token.h"
#include "lexer.h"
#include "libft.h"
#include "syntax_coloring.h"

/*
**	Receives the address of an already existing lexer (already has an address)
**	and fills it with default values + a dup of line ( must be freed at some
**	point).
*/

int		init_lexer(t_lexer *lex, const char *line)
{
	ft_memset(lex, 0, sizeof(t_lexer));
	lex->line = ft_strdup(line);
	lex->pos = 0;
	lex->state = NULL;
	lex->state_list = NULL;
	lex->cmd_name_open = 1;
	lex->reversed_list = NULL;
	push_state(lex, DEFAULT);
	return (1);
}

int		free_lexer(t_lexer *lex)
{
	if (lex->reversed_list)
		ft_simple_lst_remove(&lex->reversed_list, NULL);
	if (lex->state_list)
		ft_simple_lst_remove(&lex->state_list, free_info);
	free(lex->line);
	return (1);
}
