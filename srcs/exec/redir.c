/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 10:50:13 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/19 18:03:01 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include "env.h"
#include "exec.h"
#include "builtin.h"
#include "line_editing.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>


static t_redir	g_redir[] =
{
	{TK_GREAT, &output_redir},
	{-1, NULL}
};


/*
**	Function used to restore all FDs after work is done.
*/

void	close_redir(t_list *redir_stack)
{
	t_list	*first;
	int		*save;

	first = redir_stack;
	while (first)
	{
		save = first->data;
		dup2(save[1], save[0]);
		close(save[1]);
		first = first->next;
	}
	ft_simple_lst_remove(&redir_stack, ft_free);
}

int		get_fd_link(t_list *redir, int io_ref)
{
	int		*save;

	while (redir)
	{
		save = redir->data;
		if (save[0] == io_ref)
			return (save[1]);
		redir = redir->next;
	}
	return (io_ref);
}
/*
**	save[0] is the original fd.
**	save[1] is the dup.
*/

void	output_redir(int io_number, char *target, t_list **redir_stack)
{
	int	target_fd;
	int	*save;

	errno = 0;
	target_fd = open(target, O_RDWR | O_CREAT);
	if (target_fd < 0)
		perror(NULL);
	chmod(target, S_IRUSR | S_IWUSR | S_IXUSR);
	if (target_fd >= 0)
	{
		save = palloc(sizeof(*save) * 2);
		save[0] = io_number;
		save[1] = dup(io_number);
		ft_simple_lst_add(redir_stack, ft_simple_lst_create(save));
		/* } */
		dup2(target_fd, io_number);
	}
}

void	exec_redir(t_ast *ast, t_list **redir_stack)
{
	t_list	*child_list;
	t_ast	*child_node;
	int		io_number;
	void	(*f)(int, char*, t_list**);
	char	*target;
	size_t	i = 0;

	child_list = ast->child;
	io_number = 1;
	while (child_list)
	{
		child_node = child_list->data;
		if (child_node->token->id == TK_IO_NUMBER)
			io_number = ft_atoi(child_node->token->value);
		else if TK_IS_REDIR((child_node->token->id))
		{
			while (g_redir[i].f && g_redir[i].id != child_node->token->id)
				i++;
			f = g_redir[i].f;
		}
		else
			target = child_node->token->value;
		child_list = child_list->next;
	}
	if (target)
		f(io_number, target, redir_stack);
}
