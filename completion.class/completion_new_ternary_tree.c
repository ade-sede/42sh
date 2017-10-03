/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_new_ternary_tree.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 05:14:27 by bmickael          #+#    #+#             */
/*   Updated: 2017/09/10 05:14:29 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_completion.h"

static t_ternary_tree	*ternary_tree_new(char c)
{
	t_ternary_tree *new;

	if (!(new = ft_memalloc(sizeof(t_ternary_tree))))
		exit(EXIT_FAILURE);
	new->c = c;
	return (new);
}

t_ternary_tree			*ternary_tree_new_down(char *str, char *cur)
{
	t_ternary_tree *res;
	t_ternary_tree *tmp;

	res = ternary_tree_new(*cur);
	tmp = res;
	cur++;
	while (*cur)
	{
		tmp->down = ternary_tree_new(*cur);
		if (*cur)
			tmp = tmp->down;
		cur++;
	}
	if (!(tmp->match = ft_strdup(str)))
		exit(EXIT_FAILURE);
	return (res);
}
