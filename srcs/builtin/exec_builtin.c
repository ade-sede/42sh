/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 05:07:29 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 11:36:50 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "builtin.h"
#include "exec.h"
#include <sys/wait.h>
#include <fcntl.h>

static t_builtin	g_builtin[] =
{
	{"cd", &builtin_cd},
	{"exit", &builtin_exit},
	{"env", &builtin_env},
	{"unsetenv", &builtin_unsetenv},
	{"setenv", &builtin_setenv},
	{"echo", &builtin_echo},
	{NULL, NULL}
};

static void	redir_pipe_built(int *p_right, int *p_left)
{
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
}

void		*get_exec_builtin(const char **argv)
{
	int			i;

	i = 0;
	while (g_builtin[i].key && !ft_strequ(g_builtin[i].key, argv[0]))
		i++;
	return (g_builtin[i].f);
}

int			exec_builtin_father(t_env *env, pid_t child, int *p_left)
{
	if (child > 0)
	{
		if (p_left)
			close(p_left[WRITE_END]);
		wait(&child);
		env->previous_exit = WEXITSTATUS(child);
	}
	return (1);
}

int			exec_builtin(t_env *env, const char **argv, t_lst_head *head)
{
	pid_t		child;
	int			*p_right;
	int			*p_left;
	int			save;
	int			(*f)(t_env*, const char**);

	p_right = (head->middle != NULL) ? head->middle->data : NULL;
	p_left = (head->middle && head->middle->prev) ? \
			head->middle->prev->data : NULL;
	if ((f = get_exec_builtin(argv)) == NULL)
		return (0);
	if (p_left && !p_right)
	{
		save = dup(STDIN_FILENO);
		close(p_left[WRITE_END]);
		dup2(p_left[READ_END], STDIN_FILENO);
	}
	if ((child = (p_right) ? fork() : 0) == 0)
	{
		redir_pipe_built(p_right, p_left);
		env->previous_exit = f(env, argv);
		(p_left && !p_right) ? dup2(save, STDIN_FILENO) : 0;
		(p_right) ? exit(env->previous_exit) : 0;
	}
	return (exec_builtin_father(env, child, p_left));
}
