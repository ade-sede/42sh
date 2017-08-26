/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ternary_search_tree_add.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/26 21:13:27 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/26 21:13:44 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

void	ternary_tree_insert_left(t_ternary_tree *node, char *cur, char *str)
{
	t_ternary_tree *new_down;
	t_ternary_tree *left;

	left = NULL;
	new_down = ternary_tree_new_down(str, cur);
	left = node->left;
	node->left = new_down;
	if (left)
		new_down->left = left;
}

void	ternary_tree_insert_right(t_ternary_tree *node, char *cur, char *str)
{
	t_ternary_tree *new_down;
	t_ternary_tree *right;

	right = NULL;
	new_down = ternary_tree_new_down(str, cur);
	right = node->right;
	node->right = new_down;
	if (right)
		new_down->right = right;
}

void	ternary_tree_insert_down(t_ternary_tree *node, char *cur, char *str)
{
	t_ternary_tree *new_down;

	if (!*cur)
		return ;
	new_down = ternary_tree_new_down(str, cur);
	node->down = new_down;
}

void	ternary_tree_add(t_ternary_tree *node, char *cur, char *str)
{
	if (*cur < node->c && (!node->left || (node->left && *cur > node->left->c)))
		return (ternary_tree_insert_left(node, cur, str));
	else if (*cur > node->c && (!node->right || \
				(node->right && *cur < node->right->c)))
		return (ternary_tree_insert_right(node, cur, str));
	else if (*cur < node->c)
		return (ternary_tree_add(node->left, cur, str));
	else if (*cur > node->c)
		return (ternary_tree_add(node->right, cur, str));
	else if (*cur == node->c && node->down)
		return (ternary_tree_add(node->down, cur + 1, str));
	else if (*cur == node->c && !node->down)
		return (ternary_tree_insert_down(node, cur + 1, str));
}
