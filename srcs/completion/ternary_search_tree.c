/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ternary_search_tree.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:13:54 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

t_ternary_tree	*ternary_tree_new_down(char *str, char *cur)
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
	tmp->match = ft_strdup(str);
	return (res);
}

t_ternary_tree	*ternary_tree_new(char c)
{
	t_ternary_tree *new;

	if (!(new = ft_memalloc(sizeof(t_ternary_tree))))
		exit(1);
	new->c = c;
	return (new);
}
