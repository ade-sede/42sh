#include "libft.h"
#include "env.h"
#include "sys/wait.h"

void	ft_exec_bin_absolute(t_env *env, const char **argv)
{
	if (access(argv[0], F_OK) == -1)
		exit(return_failure(argv[0], " :no such file or directory"));
	else if (access(argv[0], X_OK) == -1)
		exit(return_failure(argv[0], " :permission denied "));
	else if (execve(argv[0], (char**)argv, env->environ) != -1)
		exit(return_failure(argv[0], " :command not found"));
}

void	ft_exec_bin_path(t_env *env, const char **argv)
{
	char	*bin;
	char	*path; 
	char	**paths;
	int	i;

	i = 0;
	if (!(path = env_getenv((const char**)env->environ, "PATH", NULL)))
		exit(return_failure("path unset", NULL));
	//printf("%s\n", path);
	paths = ft_strsplit(path + 5, ":");
	while (paths[i])
	{
		//printf("%s\n", paths[i]);
		bin = ft_strsurround(paths[i], "/", argv[0]);
		if (access(bin, F_OK) == 0)
		{
			if (access(bin, X_OK) == -1)
			{
				ft_arraydel(&paths);
				exit(return_failure(bin, " :permission denied "));
			}
			execve(bin, (char**)argv, env->environ);
		}
		free(bin);
		i++;
	}
	ft_arraydel(&paths);
	exit(return_failure(argv[0], " :commmand not found"));
}

int	fork_exec_bin(t_env *env, const char **argv)
{
	pid_t		child;

	child = fork();
	if (child == 0)
	{
		if (ft_strchr(argv[0], '/'))
			ft_exec_bin_absolute(env, argv);
		else
			ft_exec_bin_path(env, argv);
	}
	if (child > 0)
	{
		env->child_pid = child;
		wait(&child);
		env->previous_exit = WEXITSTATUS(child);
		return (WEXITSTATUS(child));
	}
	return (1);
}
