/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 10:50:13 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/19 11:28:20 by ade-sede         ###   ########.fr       */
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

static t_redir	g_redir[] =
{
	{TK_GREAT, &output_redir},
	{-1, NULL}
};

void	output_redir(int io_number, char *target)
{
	int	target_fd;

	errno = 0;
	target_fd = open(target, O_RDWR | O_CREAT);
	if (target_fd < 0)
		perror(NULL);
	dup2(target_fd, io_number);
}

void	exec_redir(t_ast *ast)
{
	t_list	*child_list;
	t_ast	*child_node;
	int		io_number;
	void	(*f)(int, char*);
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
		f(io_number, target);
}
