/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comple_bin_matches.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 22:41:05 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/15 22:41:13 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "env.h"
#include "completion.h"

void	comple_bin_matches_extract_tree(t_ternary_tree *node, char **matches,
		int *i)
{
	if (!node)
		return ;
	if (node->match)
	{
		matches[*i] = ft_strdup(node->match);
		*i = *i + 1;
	}
	comple_bin_matches_extract_tree(node->left, matches, i);
	comple_bin_matches_extract_tree(node->down, matches, i);
	comple_bin_matches_extract_tree(node->right, matches, i);
}

void	comple_bin_matches_tripping_tree(t_ternary_tree *node, char **matches,
		char *cur)
{
	int	i;

	i = 0;
	if (!cur[0] || !node)
		return (comple_bin_matches_extract_tree(node, matches, &i));
	if (*cur < node->c && (!node->left || (node->left && *cur > node->left->c)))
		return ;
	else if (*cur > node->c
			&& (!node->right || (node->right && *cur < node->right->c)))
		return ;
	else if (*cur < node->c)
		return (comple_bin_matches_tripping_tree(node->left, matches, cur));
	else if (*cur > node->c)
		return (comple_bin_matches_tripping_tree(node->right, matches, cur));
	else if (*cur == node->c && node->down)
		return (comple_bin_matches_tripping_tree(node->down, matches, cur + 1));
	else if (*cur == node->c && !node->down)
		return ;
}

char	**comple_bin_matches(t_line *line, t_comple *c)
{
	char		**matches;

	c->to_replace = get_start_word_cursor(line);
	matches = ft_memalloc(sizeof(char *) * 2000);
	comple_bin_matches_tripping_tree(singleton_env()->tree, matches,
			c->current_word);
	return (matches);
}
