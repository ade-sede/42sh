/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 14:19:04 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/24 15:12:48 by ade-sede         ###   ########.fr       */
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

static void	redir_pipe_bin(t_lst_head *head)
{
	int			*p_right;
	int			*p_left;
	t_list_d	*cur;

	cur = head->middle;
	p_right = (cur != NULL) ? cur->data : NULL;
	p_left = (cur && cur->prev) ? cur->prev->data : NULL;
		if (p_right)
		{
#ifdef PIPE_DEBUG
			if (!p_left)
				dprintf(2, "Binary is on the left of the pipe // dup 1 to p_right[WRITE_END], close p_right[READ_END]\n");//			REMOVE		
#endif
				close(p_right[READ_END]);
				dup2(p_right[WRITE_END], STDOUT_FILENO);
			if (p_left)
			{
#ifdef PIPE_DEBUG
				dprintf(2, "Command is in between 2 pipes. dup 1 to p_right[WRITE_END], dup 0 to p_left[READ_END], closing p_right[READ_END] & p_left[WRITE_END]\n");//			REMOVE		
#endif
				close(p_left[WRITE_END]);
				dup2(p_left[READ_END], STDIN_FILENO);
			}
		}
		else
		{
			if (p_left)
			{
#ifdef PIPE_DEBUG
				dprintf(2, "Command is on the right of the pipe // dup 0 to p_left[READ_END], closing p_left[WRITE_END]\n");//			REMOVE		
#endif
				close(p_left[WRITE_END]);
				dup2(p_left[READ_END], STDIN_FILENO);
			}
		}
}

static void	close_parent_bin(t_lst_head *head)
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
		dprintf(2, "closing p_left[WRITE_END] in parent process \n");//			REMOVE		
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
#ifndef NO_TERMCAPS
	conf_term_out();
#endif
	child = fork();
	if (child == 0)
	{
		if (p_right != NULL || p_left != NULL)
			redir_pipe_bin(head);
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
			close_parent_bin(head);
		env->child_pid = child;
		wait(&child);
#ifndef NO_TERMCAPS
		conf_term_in();
#endif
		env->previous_exit = WEXITSTATUS(child);
		return (WEXITSTATUS(child));
	}
	return (1);
}
