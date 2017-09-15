/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 22:49:54 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/15 22:52:48 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include "env.h"
#include "exec.h"
#include "builtin.h"
#include "color.h"
#include "line_editing.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <errno.h>
#include <signal.h>

int		p_right(t_pipe *pr, t_ast *ast, t_lst_head *head)
{
	pid_t		child;

	child = fork();
	if (child == -1)
	{
		return (0);
	}
	if (child == 0)
	{
		close(pr->p[READ_END]);
		dup2(pr->p[WRITE_END], STDOUT_FILENO);
		exec_simple_command(ast, head);
		exit(0);
	}
	else
	{
		pr->pid = child;
		return (1);
	}
	return (1);
}

int		p_both(t_pipe *pr, t_pipe *pl, t_ast *ast, t_lst_head *head)
{
	pid_t		child;

	child = fork();
	if (child == -1)
	{
		return (0);
	}
	if (child == 0)
	{
		dup2(pl->p[READ_END], STDIN_FILENO);
		close(pl->p[WRITE_END]);
		close(pr->p[READ_END]);
		dup2(pr->p[WRITE_END], STDOUT_FILENO);
		exec_simple_command(ast, head);
		exit(0);
	}
	else
	{
		close(pl->p[WRITE_END]);
		close(pl->p[READ_END]);
		pr->pid = child;
	}
	return (1);
}

int		wait_zombies(t_lst_head *head)
{
	t_list_d	*cur;
	t_pipe		*pipe;
	int			ret;

	cur = head->first;
	while (cur)
	{
		pipe = (t_pipe *)cur->data;
		if (pipe)
		{
			if (pipe->pid != 0)
				waitpid(pipe->pid, &ret, 0);
		}
		cur = cur->next;
	}
	return (1);
}

int		p_left(t_pipe *pl, t_ast *ast, t_lst_head *head)
{
	int		save;

	save = dup(STDIN_FILENO);
	dup2(pl->p[READ_END], STDIN_FILENO);
	close(pl->p[WRITE_END]);
	exec_simple_command(ast, head);
	close(pl->p[READ_END]);
	dup2(save, STDIN_FILENO);
	close(save);
	wait_zombies(head);
	return (1);
}

int		check_pipes(t_ast *ast, t_lst_head *head)
{
	t_list_d	*cur;
	t_pipe		*pr;
	t_pipe		*pl;

	cur = head->middle;
	pr = (cur != NULL) ? cur->data : NULL;
	pl = (cur && cur->prev) ? cur->prev->data : NULL;
	if (pr && !pl)
		p_right(pr, ast, head);
	else if (pr && pl)
		p_both(pr, pl, ast, head);
	else if (!pr && pl)
		p_left(pl, ast, head);
	else
		exec_simple_command(ast, head);
	return (1);
}
