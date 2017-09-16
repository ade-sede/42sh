/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ternary_search_tree.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 22:41:05 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/16 02:27:01 by vcombey          ###   ########.fr       */
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
/*
**	void			ternary_tree_print(t_ternary_tree *node)
**	{
**		if (!node)
**			return ;
**		printf("c is %c\n", node->c);
**		if (node->match)
**			printf("match is %s\n", node->match);
**		if (node->left)
**			printf("\n left \n");
**		ternary_tree_print(node->left);
**		if (node->down)
**			printf("\n down \n");
**		ternary_tree_print(node->down);
**		if (node->right)
**			printf("\n right\n");
**		ternary_tree_print(node->right);
**	}
*/
/*
**	void			test_ternary_tree()
**	{
**		char	*str;
**		t_ternary_tree *tree;
**		str = "ab";
**		tree = ternary_tree_new_down(str, str);
**		ternary_tree_print(tree);
**		str = "ba";
**		printf("\n test 1\n");
**		ternary_tree_add(tree, str, str);
**		ternary_tree_print(tree);
**	}
*/
