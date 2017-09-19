#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "exec.h"
#include "line_editing.h"
#include "lexer.h"
#include "parser.h"
#include <errno.h>
#include <stdio.h>

static int	safe_open(char *target, int mode)
{
	int		target_fd;

	target_fd = -1;
	if (mode & O_CREAT)
		target_fd = open(target, mode, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		target_fd = open(target, mode);
	if (target_fd == -1)
	{
		perror("open: ");
	}
	return (target_fd);
}

int			redir_open_file(char *target, t_token_id id)
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
	target_fd = safe_open(target, mode);
	return (target_fd);
}

/*
**	save[0] is the original fd (source) (fildes1)
**	save[1] The duplicate of the source fd save[0] (dup(io_number))
**	save[2] is the fd of the opened file. -1 if no file was opened. (fildes2)
**	save[3] is a flag that indicates if save[1](target) is a fd that should or
**	not be closed. If the fd shouldnt be closed its value is 1.
**	Must be careful about never closing stdin stdout or stderr.
*/

/*
**	Function used to restore all FDs after work is done.
*/

void		close_dup(t_list *redir_stack)
{
	t_list	*first;
	int		*save;

	first = redir_stack;
	redir_stack = first;
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
**	The function that actually duplictes the fd, and pushes \
**	the operation onto our stack.
*/

void		push_dup(int io_number, int target_fd, int natural_fd, \
		t_list **redir_stack)
{
	int	*save;

	save = palloc(sizeof(*save) * 4);
	save[0] = io_number;
	save[1] = dup(io_number);
	save[2] = target_fd;
	save[3] = natural_fd;
	if (target_fd == -2)
		close(io_number);
	ft_simple_lst_pushback(redir_stack, ft_simple_lst_create(save));
}

int			exec_dup(t_list *redir_stack)
{
	int		*save;

	while (redir_stack)
	{
		save = redir_stack->data;
		dup2(save[2], save[0]);
		redir_stack = redir_stack->next;
	}
	return (1);
}
