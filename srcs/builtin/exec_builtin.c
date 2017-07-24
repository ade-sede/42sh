/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 14:43:38 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/24 13:31:19 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "builtin.h"
#include "exec.h"
#include <fcntl.h>

t_builtin g_builtin[] =
{
	{"cd", &builtin_cd},
	{"exit", &builtin_exit},
	{"env", &builtin_env},
	{"unsetenv", &builtin_unsetenv},
	{"setenv", &builtin_setenv},
	{"echo", &builtin_echo},
	{NULL, NULL}
};

int		exec_builtin(t_env *env, const char **argv, t_lst_head *head)
{
	int			i;
	pid_t		child;
	int			*p_right;
	int			*p_left;
	t_list_d	*cur;
	int			save;
	int			(*f)(t_env*, const char**);

	cur = head->middle;
	p_right = (cur != NULL) ? cur->data : NULL;
	p_left = (cur && cur->prev) ? cur->prev->data : NULL;

	child = 0;
	i = 0;
	while (g_builtin[i].key && !ft_strequ(g_builtin[i].key, argv[0]))
		i++;
	f = g_builtin[i].f;
	if (f == NULL)
		return (0);
	if (p_right)
		child = fork();
	if (p_left && !p_right)
	{
			save = dup(STDIN_FILENO);
			close(p_left[WRITE_END]);
			dup2(p_left[READ_END], STDIN_FILENO);
	}
	if (child == 0) // The child if we forked, the main process otherwise.
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
		env->previous_exit = f(env, argv);
		if (p_left && !p_right)
			dup2(save, STDIN_FILENO);
		if (p_right)
			exit(env->previous_exit);
	}
	else if (child > 0)
	{
		if (p_left)
			close(p_left[WRITE_END]);
		wait(&child);
		env->previous_exit = WEXITSTATUS(child);
	}
	return (1);
}
