/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 19:35:10 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 12:00:57 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "syntax_coloring.h"

int		push_state_le(t_lexer *lex, int new_state)
{
	struct s_info	*info;
	t_list			*node;

	info = create_state_info();
	info->state = new_state;
	info->nest = 0;
	info->count = 0;
	node = ft_simple_lst_create(info);
	ft_simple_lst_pushback(&lex->state_list, node);
	lex->state = node;
	ft_putstr_fd(get_color(info->state), 2);
	return (1);
}

int		consume_input_le(t_lexer *lex, t_line *line)
{
	struct s_info	*info;

	write_term(line, lex->pos);
	info = lex->state->data;
	w_addchar(&info->value, lex->line[lex->pos]);
	lex->pos++;
	info->count++;
	return (1);
}

/*
**	Est utilise pour finir l'etat courrant.
**	L'etat courrant doit etre disponible dans *info
**	L'etat courrant doit disparaitre de la state_list
**	le pointeur sur l'etat courrant, doit etre remi sur l'etat precedant.
*/

int		pop_state_le(t_lexer *lex, struct s_info **info)
{
	struct s_info *parent_info;

	free_info(*info);
	*info = lex->state->data;
	ft_simple_lst_del_one(&lex->state_list, lex->state, NULL);
	lex->state = ft_last_simple_lst(lex->state_list);
	parent_info = lex->state->data;
	w_addstr(&parent_info->value, (*info)->value.str);
	parent_info->count += (*info)->count;
	ft_putstr_fd(get_color(parent_info->state), 2);
	return (1);
}

int		change_state_le(t_lexer *lex, int new_state)
{
	((struct s_info*)lex->state->data)->state = new_state;
	ft_putstr_fd(get_color(new_state), 2);
	return (1);
}
