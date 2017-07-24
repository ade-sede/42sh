/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 14:37:06 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/24 19:02:53 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "exec.h"
#include "line_editing.h"
#include "lexer.h"
#include "parser.h"

static t_redir	g_redir[] =
{
	{TK_GREAT, &file_redir},
	{TK_DGREAT, &file_redir},
	{TK_LESS, &file_redir},
	{TK_LESSGREAT, &file_redir},
	{TK_LESSAND, &merge_fd},
	{TK_GREATAND, &merge_fd},
	{TK_HERE, &heredoc},
	{-1, NULL}
};

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
	if (id != TK_LESS)
	{
		mode |= (id == TK_LESSGREAT) ? O_RDWR : O_WRONLY;
		if (access(target, F_OK) == -1)
			mode |= O_CREAT;
		if (id == TK_DGREAT)
			mode |= O_APPEND;
		else if (id != TK_LESSGREAT && id != TK_DGREAT)
			mode |= O_TRUNC;
	}
	if (mode & O_CREAT)
		target_fd = open(target, mode, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		target_fd = open(target, mode);
	return (target_fd);
}

/*
**	save[0] is the original fd (source)
**	save[1] The duplicate of the source fd save[0]
**	save[2] is the fd of the opened file. -1 if no file was opened. (target)
**	save[3] is a flag that indicates if save[1](target) is a fd that should or
**	not be closed. If the fd shouldnt be closed its value is 1.
**	Must be careful about never closing stdin stdout or stderr.
*/

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
		if (save[3] != TRUE)
			close(save[2]);
		close(save[1]);
		first = first->next;
	}
	ft_simple_lst_remove(&redir_stack, ft_free);
}

/*
**	The function that actually duplictes the fd, and pushes the operation onto our stack.
*/

void	exec_dup(int io_number, int target_fd, int natural_fd, t_list **redir_stack)
{
	int	*save;

	save = palloc(sizeof(*save) * 4);
	save[0] = io_number;
	save[1] = dup(io_number);
	save[2] = target_fd;
	save[3] = natural_fd;
	ft_simple_lst_add(redir_stack, ft_simple_lst_create(save));
	dup2(target_fd, io_number);
}

/*
**	Fd merging with op >& and <&
*/

void	heredoc(int io_number, char *target, t_list **redir_stack, t_token_id id)
{
	int		fd;
	char		*buff;

	(void)id;
	/* buff = NULL; */
	if (io_number == -1)
		io_number = 0;
	errno = 0;
	if ((fd = open("/tmp/42sh_heredoc", O_WRONLY|O_CREAT|O_EXCL|O_TRUNC, 0600)) < 0)
		dprintf(2, "Open : %s\n", strerror(errno));
	while (fd >= 0 && buff && !ft_strequ(buff, target))
	{
		load_prompt(singleton_env(), singleton_line(), "heredoc", "heredoc> ");
		buff = line_editing_get_input(singleton_env(), singleton_line(), singleton_hist());
		if (!ft_strequ(buff, target))
			write(fd, buff, ft_strlen(buff));
	}
	close(fd);
	errno = 0;
	if ((fd = open("/tmp/42sh_heredoc", O_RDONLY)) > 0)
		dprintf(2, "Open : %s\n", strerror(errno));
	exec_dup(io_number, fd, FALSE, redir_stack);
}

void	merge_fd(int io_number, char *target, t_list **redir_stack, t_token_id id)
{
	int	target_fd;
	int	natural_fd;

	natural_fd = TRUE;
	if (io_number == -1)
		io_number = (id == TK_LESSAND) ? STDIN_FILENO : STDOUT_FILENO;
	if (ft_strequ(target, "-"))
	{
		natural_fd = FALSE;
		target_fd = open("/dev/null", O_WRONLY);
	}
	else
		target_fd = ft_atoi(target);
	errno = 0;
	if (target_fd >= STDIN_FILENO && (fcntl(target_fd, F_GETFD) != -1 && errno != EBADF))
		exec_dup(io_number, target_fd, natural_fd, redir_stack);
}

void	file_redir(int io_number, char *target, t_list **redir_stack, t_token_id id)
{
	int	target_fd;

	if (io_number == -1)
		io_number = (id == TK_LESS || id == TK_LESSGREAT) ? STDIN_FILENO : STDOUT_FILENO;
	target_fd = redir_open_file(target, id);
	if (target_fd >= STDIN_FILENO)
		exec_dup(io_number, target_fd, FALSE, redir_stack);

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
			while (g_redir[i].f && g_redir[i].id != (int)child_node->token->id)
				i++;
			f = g_redir[i].f;
			id = child_node->token->id;
		}
		else
			target = child_node->token->value;
		child_list = child_list->next;
	}
	if (f)
		f(io_number, target, redir_stack, id);
}
