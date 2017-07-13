/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 14:19:04 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/13 14:25:23 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "sys/wait.h"
#include <stdio.h>

/*
**		We forked, this is called in the child process. Try to use the absolute
**		path to the binary.
*/

void		ft_exec_bin_absolute(t_env *env, const char **argv)
{
	if (access(argv[0], F_OK) == -1)
		exit(return_failure(argv[0], " :no such file or directory"));
	else if (access(argv[0], X_OK) == -1)
		exit(return_failure(argv[0], " :permission denied "));
	else if (execve(argv[0], (char**)argv, env->environ) != -1)
		exit(return_failure(argv[0], " :command not found"));
}

/*
**		We forked, this is called in the child process. Looks for the binary in
**		the path, exit_failure if we cant find id.
*/

static void	failure(const char *argv, char **paths)
{
	ft_arraydel(&paths);
	exit(return_failure(argv, " :commmand not found"));
}

void		ft_exec_bin_path(t_env *env, const char **argv)
{
	char	*bin;
	char	*path;
	char	**paths;
	int		i;

	i = 0;
	if (!(path = env_getenv((const char**)env->environ, "PATH", NULL)))
		exit(return_failure("PATH variable not set. Use Setenv to set", NULL));
	paths = ft_strsplit(path, ":");
	while (paths[i])
	{
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
	failure(argv[0], paths);
}

int			fork_exec_bin(t_env *env, const char **argv)
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
