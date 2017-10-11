#include "completion.h"
#include "line_editing.h"
#include <string.h>

void	create_ternary_tree_dir(char *dir_path, t_env *env)
{
	struct dirent	*dirent;
	DIR				*dir;
	char			*name;

	dir = NULL;
	if (!(dir = opendir(dir_path)))
		return ;
	while ((dirent = readdir(dir)) != NULL)
	{
		name = dirent->d_name;
		if (name[0] != '.' && ft_is_executable(dir_path, name))
		{
			if (!env->tree)
				env->tree = ternary_tree_new_down(name, name);
			else
				ternary_tree_add(env->tree, name, name);
		}
	}
	closedir(dir);
}

void	free_ternary_tree(t_ternary_tree *node)
{
	t_ternary_tree	*left;
	t_ternary_tree	*down;
	t_ternary_tree	*right;

	if (!node)
		return ;
	left = node->left;
	right = node->right;
	down = node->down;
	if (node->match)
		free(node->match);
	free_ternary_tree(left);
	free_ternary_tree(down);
	free_ternary_tree(right);
	free(node);
}

int		create_ternary_tree(t_env *env)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	if (!(path = env_getenv((const char**)env->environ, "PATH", NULL)))
		return (0);
	paths = ft_strsplit(path, ":");
	while (paths[i])
	{
		create_ternary_tree_dir(paths[i], env);
		i++;
	}
	ft_arraydel(&paths);
	return (1);
}
