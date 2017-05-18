/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 16:10:18 by vcombey           #+#    #+#             */
/*   Updated: 2017/05/18 15:37:33 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include "minishell.h"

void	ft_exec_bin_absolute(t_env *env, const char **argv)
{
	if (access(argv[0], F_OK) == -1)
		return_failure(argv[0], " :no such file or directory");
	else if (access(argv[0], X_OK) == -1)
		return_failure(argv[0], " :permission denied ");
	else if (execve(argv[0], argv, env->environ) != -1)
		return_failure(argv[0], " :command not found");
}

void	ft_exec_bin_path(t_env *env, const char **argv)
{
	char	*bin;
	t_list	tmp;

	tmp = env->path;
	while (tmp)
	{
		bin = ft_surround(tmp->data, "/", argv[0]);
		if (access(bin, F_OK) == 0)
		{
			if (access(bin, X_OK) == -1)
				return_failure(bin, " :permission denied ");
			execve(bin, argv, env->environ);
		}
		free(bin);
		tmp = tmp->next;
	}
	return_failure(argv[0], " :no such file or directory");
}

int	fork_exec_bin(t_env *env, const char **argv)
{
	pid_t		child;

	child = fork();
	if (child == 0)
	{
		if (ft_strchr(argv[0], '/'))
			ft_exec_bin_absolute(argv, env);
		else
			ft_exec_bin_path(argv, env);
	}
	if (child > 0)
	{
		wait(&child);
		env->previous_exit = WEXITSTATUS(child);
		return (WEXITSTATUS(child));
	}
	return (1);
}
