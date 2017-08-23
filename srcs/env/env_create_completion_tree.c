#include "completion.h"
#include "line_editing.h"
	#include <stdio.h>
#include <string.h>

void	create_ternary_tree_dir(char *dir_path, t_env *env)
{
	struct dirent	*dirent;
	DIR		*dir;

	dir = NULL;
	if (!(dir = opendir(dir_path)))
		return ;
	while ((dirent = readdir(dir)) != NULL)
	{
		//	printf("\nd_name: %s \n", dirent->d_name);
		if (dirent->d_name[0] != '.')
		{
			if (!env->tree)
			{
				if ((dirent = readdir(dir)) != NULL)
					env->tree = ternary_tree_new_down(dirent->d_name, dirent->d_name);
				ternary_tree_print(env->tree);
			}
			else
			{
				ternary_tree_add(env->tree, dirent->d_name, dirent->d_name);
			}
		}

	}
	printf("\n TEST \n");
	//ternary_tree_print(env->tree);
	closedir(dir);
}

int	create_ternary_tree(t_env *env)
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
ternary_tree_print(env->tree);
	ft_arraydel(&paths);
	return (1);
}
