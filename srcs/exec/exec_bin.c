/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 14:19:04 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/23 19:49:43 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "sys/wait.h"
#include "exec.h"
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

static void	redir_pipe(t_lst_head *head)
{
	int			*p_right;
	int			*p_left;
	t_list_d	*cur;

	cur = head->middle;
	p_right = (cur != NULL) ? cur->data : NULL;
	p_left = (cur && cur->prev) ? cur->prev->data : NULL;
#ifdef PIPE_DEBUG
	dprintf(2, RED"----------------------------------------------------\n"RESET);//			REMOVE		
	dprintf(2, "Addr of p_right = %p\nAddr of p_left = %p\n", p_right, p_left);//			REMOVE		
#endif
		if (p_right)
		{
			if (!p_left)
			{
#ifdef PIPE_DEBUG
				dprintf(2, "Left // Write side\n");//			REMOVE		
#endif
				close(p_right[READ_END]);
				dup2(p_right[WRITE_END], STDOUT_FILENO);
			}
			else
			{
#ifdef PIPE_DEBUG
				dprintf(2, "Between // Read side + Write side\n");//			REMOVE		
#endif
				close(p_right[READ_END]);
				close(p_left[WRITE_END]);
				dup2(p_right[WRITE_END], STDOUT_FILENO);
				dup2(p_left[READ_END], STDIN_FILENO);
			}
		}
		else
		{
			if (p_left)
			{
#ifdef PIPE_DEBUG
				dprintf(2, "Right // Read side\n");//			REMOVE		
#endif
				close(p_left[WRITE_END]);
				dup2(p_left[READ_END], STDIN_FILENO);
			}
		}
#ifdef PIPE_DEBUG
	dprintf(2, RED"----------------------------------------------------\n"RESET);//			REMOVE		
#endif
}

static void	close_parent(t_lst_head *head)
{
	int			*p_right;
	int			*p_left;
	t_list_d	*cur;

	cur = head->middle;
	p_right = (cur != NULL) ? cur->data : NULL;
	p_left = (cur && cur->prev) ? cur->prev->data : NULL;
	/* if (p_right) */
	/* { */
/* #ifdef PIPE_DEBUG */
	/* 	dprintf(2, "closing p_right[WRITE_END] in parent \n");//			REMOVE */		
/* #endif */
	/* 	/1* close(p_right[WRITE_END]); *1/ */
	/* } */
	if (p_left)
	{
#ifdef PIPE_DEBUG
		dprintf(2, "closing p_left[WRITE_END] in parent \n");//			REMOVE		
		/* dprintf(2, "closing p_left[READ_END] in parent \n");//			REMOVE */		
#endif
		close(p_left[WRITE_END]);
		/* close(p_left[READ_END]); */
	}
}

int			fork_exec_bin(t_env *env, const char **argv, t_lst_head *head)
{
	pid_t		child;
	int			*p_right;
	int			*p_left;
	t_list_d	*cur;

	cur = head->middle;
	p_right = (cur != NULL) ? cur->data : NULL;
	p_left = (cur && cur->prev) ? cur->prev->data : NULL;
	child = fork();
	if (child == 0)
	{
		if (p_right != NULL || p_left != NULL)
			redir_pipe(head);
#ifdef PIPE_DEBUG
		else
			dprintf(2, "Not related to a pipe !!\n");//			REMOVE		
#endif
		if (ft_strchr(argv[0], '/'))
			ft_exec_bin_absolute(env, argv);
		else
			ft_exec_bin_path(env, argv);
	}
	if (child > 0)
	{
		if (p_right != NULL || p_left != NULL)
			close_parent(head);
		env->child_pid = child;
		wait(&child);
		env->previous_exit = WEXITSTATUS(child);
		return (WEXITSTATUS(child));
	}
	return (1);
}
