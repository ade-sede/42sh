/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 05:07:29 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 11:01:06 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "sys/wait.h"
#include "exec.h"
#include <stdio.h>
#include "hash_table.h"

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
	else if (execve(argv[0], (char**)argv, env->environ) == -1)
		exit(return_failure(argv[0], " :command not found"));
	exit(1);
}

/*
**		We forked, this is called in the child process. Looks for the binary in
**		the path, exit_failure if we cant find id.
*/

void		ft_exec_bin_path(t_env *env, const char **argv)
{
	char	*bin;

	bin = hash_get(env->hash_table, (char *)argv[0]);
	if (access(bin, F_OK) == 0)
	{
		if (access(bin, X_OK) == -1)
			exit(return_failure(bin, " :permission denied "));
		else if (execve(bin, (char**)argv, env->environ) == -1)
			exit(return_failure(argv[0], " :command not found"));
	}
	exit(return_failure((const char *)*argv, " :commmand not found"));
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
		close(p_right[READ_END]);
		dup2(p_right[WRITE_END], STDOUT_FILENO);
		if (p_left)
		{
			close(p_left[WRITE_END]);
			dup2(p_left[READ_END], STDIN_FILENO);
		}
	}
	else
	{
		if (p_left)
		{
			close(p_left[WRITE_END]);
			dup2(p_left[READ_END], STDIN_FILENO);
		}
	}
}

static void	close_parent_bin(t_lst_head *head)
{
	int			*p_left;
	t_list_d	*cur;

	cur = head->middle;
	p_left = (cur && cur->prev) ? cur->prev->data : NULL;
	if (p_left)
		close(p_left[WRITE_END]);
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
	conf_term_normal();
	no_handle_signals();
	if ((child = fork()) == 0)
	{
		(p_right || p_left) ? redir_pipe_bin(head) : 0;
		ft_strchr(argv[0], '/') ? ft_exec_bin_absolute(env, argv) : \
			ft_exec_bin_path(env, argv);
	}
	if (child > 0)
	{
		(p_right || p_left) ? close_parent_bin(head) : 0;
		env->child_pid = child;
		wait(&child);
		conf_term_canonical();
		return (env->previous_exit = WEXITSTATUS(child));
	}
	return (1);
}
