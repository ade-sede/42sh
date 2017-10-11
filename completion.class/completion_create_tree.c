/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_create_tree.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 05:13:40 by bmickael          #+#    #+#             */
/*   Updated: 2017/09/10 05:13:42 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_completion.h"
#include "common/messages.h"
#include "libshell/is_runnable.h"

static int	create_ternary_tree_dir(struct s_completion *ctx, char *dir_path)
{
	struct dirent	*dirent;
	DIR				*dir;

	if (!(dir = opendir(dir_path)))
	{
		return (warning("create_ternary_tree_dir",
		"Unable to open path", -1));
	}
	while ((dirent = readdir(dir)) != NULL)
	{
		if (dirent->d_name[0] != '.' &&
		!is_runnable(dir_path, dirent->d_name))
		{
			if (!ctx->tree)
			{
				ctx->tree =
				ternary_tree_new_down(dirent->d_name, dirent->d_name);
			}
			else
				ternary_tree_add(ctx->tree, dirent->d_name, dirent->d_name);
		}
	}
	if (closedir(dir) < 0)
		return (warning("create_ternary_tree_dir", "Unable to close path", -1));
	return (0);
}

int			create_ternary_tree(struct s_completion *ctx, char *path)
{
	char	**paths;
	int		i;

	i = 0;
	if (!(paths = ft_strsplit(path, ':')))
		exit(EXIT_FAILURE);
	while (paths[i])
	{
		create_ternary_tree_dir(ctx, paths[i]);
		i++;
	}
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
	return (0);
}

int			free_ternary_tree(t_ternary_tree **node)
{
	t_ternary_tree	*left;
	t_ternary_tree	*down;
	t_ternary_tree	*right;

	if (node == NULL)
	{
		return (error("free_ternary_tree",
		"node variable is NULL", -1));
	}
	if (*node == NULL)
		return (0);
	left = (*node)->left;
	right = (*node)->right;
	down = (*node)->down;
	if ((*node)->match)
		free((*node)->match);
	free_ternary_tree(&left);
	free_ternary_tree(&down);
	free_ternary_tree(&right);
	free(*node);
	*node = NULL;
	return (0);
}
