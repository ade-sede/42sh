/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 10:50:13 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/20 12:32:59 by ade-sede         ###   ########.fr       */
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
	{TK_GREAT, &file_redir},
	{TK_DGREAT, &file_redir},
	{TK_LESS, &file_redir},
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
		close(save[2]);
		first = first->next;
	}
	ft_simple_lst_remove(&redir_stack, ft_free);
}

/*
**	This function is used to open the file with the right options depending on
**	the operator's id. FD of the opened file will be returned.
*/

int		redir_open_file(char *target, t_token_id id)
{
	int	target_fd;
	int	mode;

	mode = 0;
	if (id == TK_LESS)
		mode |= O_RDONLY;
	else
	{
		mode |= O_WRONLY;
		if (access(target, F_OK) == -1)
			mode |= O_CREAT;
		if (id == TK_DGREAT)
			mode |= O_APPEND;
		else
			mode |= O_TRUNC;
	}
	if (mode & O_CREAT)
		target_fd = open(target, mode, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		target_fd = open(target, mode);
	return (target_fd);
}

/*
**	save[0] is the original fd.
**	save[1] is the dup.
*/

void	file_redir(int io_number, char *target, t_list **redir_stack, t_token_id id)
{
	int	target_fd;
	int	*save;

	if (io_number == -1)
		io_number = (id == TK_LESS) ? 0 : 1;
	target_fd = redir_open_file(target, id);
	if (target_fd >= 0)
	{
		save = palloc(sizeof(*save) * 3);
		save[0] = io_number;
		save[1] = dup(io_number);
		save[2] = target_fd;
		ft_simple_lst_add(redir_stack, ft_simple_lst_create(save));
		dup2(target_fd, io_number);
	}
}

void	exec_redir(t_ast *ast, t_list **redir_stack)
{
	t_list		*child_list;
	t_ast		*child_node;
	int			io_number;
	void		(*f)(int, char*, t_list**, t_token_id);
	char		*target;
	t_token_id id;
	size_t		i = 0;

	child_list = ast->child;
	io_number = -1;
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
			id = child_node->token->id;
		}
		else
			target = child_node->token->value;
		child_list = child_list->next;
	}
	f(io_number, target, redir_stack, id);
}
