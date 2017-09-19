/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:50 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:29 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipe.h"
#include "token.h"

/*
**	Those functions are called by the parser in file parser.c to edit the list
**	of pipes.
*/

/*
**	add_last_pipe adds an empty node at the end of the list of pipes and
**	creates the list if needed. Is called only once, when the parsing is over.
*/

void	add_last_pipe(t_lst_head **head)
{
	t_pipe	*spipe;

	spipe = NULL;
	if (*head == NULL)
		*head = ft_create_head(ft_double_lst_create(spipe));
	else
	{
		ft_double_lst_pushback(head, ft_double_lst_create(NULL));
		(*head)->middle = (*head)->first;
	}
}

/*
**		add_pipe creates a full node and adds it to the list of pipes and
**		creates the list if needed.
*/

void	add_pipe(t_token *token, t_lst_head **head)
{
	t_pipe	*spipe;
	int		*p;

	spipe = NULL;
	p = NULL;
	if (ft_strequ(token->value, "|"))
	{
		p = palloc(sizeof(*p) * 2);
		pipe(p);
	}
	spipe = create_pipe(p);
	if (*head == NULL)
		*head = ft_create_head(ft_double_lst_create(spipe));
	else
		ft_double_lst_pushback(head, ft_double_lst_create(spipe));
}
