/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:37 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:30 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

int		push_state(t_lexer *lex, int new_state)
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
	return (1);
}

int		consume_input(t_lexer *lex)
{
	struct s_info	*info;

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

int		pop_state(t_lexer *lex, struct s_info **info)
{
	struct s_info *parent_info;

	free_info(*info);
	*info = lex->state->data;
	ft_simple_lst_del_one(&lex->state_list, lex->state, NULL);
	lex->state = ft_last_simple_lst(lex->state_list);
	parent_info = lex->state->data;
	if ((*info)->value.str)
	{
			w_addstr(&parent_info->value, (*info)->value.str);
			parent_info->count += (*info)->count;
	}
	return (1);
}

int		change_state(t_lexer *lex, int new_state)
{
	((struct s_info*)lex->state->data)->state = new_state;
	return (1);
}
