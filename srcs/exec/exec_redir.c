/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 22:41:03 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/18 13:19:38 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	*get_exec_redir_func(t_ast *child_node)
{
	size_t		i;

	i = 0;
	while (g_redir[i].f && g_redir[i].id != (int)child_node->token->id)
		i++;
	return (g_redir[i].f);
}

/*
**	This function is used to open the file with the right options depending on
**	the operator's id. FD of the opened file will be returned.
*/

/*
**	Fd merging with op >& and <&
*/

int		merge_fd(int io_number, char *target, t_list **redir_stack, \
		t_token_id id)
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
	if (target_fd >= STDIN_FILENO && (fcntl(target_fd, F_GETFD) \
				!= -1))
		push_dup(io_number, target_fd, natural_fd, redir_stack);
	return (1);
}

int		file_redir(int io_number, char *target, t_list **redir_stack, \
		t_token_id id)
{
	int	target_fd;

	if (io_number == -1)
		io_number = (id == TK_LESS || id == TK_LESSGREAT) ? \
					STDIN_FILENO : STDOUT_FILENO;
	if ((target_fd = redir_open_file(target, id)) == -1)
		return (0);
	if (target_fd >= STDIN_FILENO)
		push_dup(io_number, target_fd, FALSE, redir_stack);
	return (1);
}

int		exec_redir(t_list *child_list, t_list **redir_stack)
{
	t_ast		*child_node;
	int			io_number;
	int			(*f)(int, char*, t_list**, t_token_id);
	char		*target;
	t_token_id	id;

	io_number = -1;
	while (child_list)
	{
		child_node = child_list->data;
		if (child_node->token->id == TK_IO_NUMBER)
			io_number = ft_atoi(child_node->token->value);
		else if (TK_IS_REDIR(child_node->token->id))
		{
			f = get_exec_redir_func(child_node);
			id = child_node->token->id;
		}
		else
			target = child_node->token->value;
		child_list = child_list->next;
	}
	if (f)
		return (f(io_number, target, redir_stack, id));
	return (0);
}
