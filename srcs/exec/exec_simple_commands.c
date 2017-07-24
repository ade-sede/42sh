/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 11:46:51 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/24 12:18:14 by ade-sede         ###   ########.fr       */
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

/*
**	Atm, this function just frees all node so that it doesnt leaks.
*/

static void	free_redir(t_ast *ast)
{
	t_list	*child_list;
	t_ast	*child_node;

	child_list = ast->child;
	while (child_list)
	{
		child_node = child_list->data;
		free_ast_node(child_node);
		child_list = child_list->next;
	}
}

/*
**	The function exec_simple_command will execute a command, step by step.
**	- Step one is I/O Redirection handling.
**	- Step two is creating an array which contains the command name, and the
**	argument to this command.
**	- Step three is sending this array to the exec function.
**
**	The ast node represents has a simple_command symbol. Treats every child one
**	by one until no childs are left.
*/

void		exec_simple_command(t_ast *ast, t_lst_head *head)
{
	t_token		*token;
	t_ast		*child_node;
	t_list		*child_list;
	size_t		i;
	const char	**argv;
	t_list		*redir_stack = NULL;

	argv = ft_memalloc(sizeof(*argv) * (4096));
	i = 0;
	child_list = ast->child;
	while (child_list)
	{
		child_node = child_list->data;
		token = child_node->token;
		if (child_node->symbol == IO_REDIRECT)
		{
			exec_redir(child_node, &redir_stack);
			free_redir(child_node);
		}
		if (child_node->symbol == CMD_NAME || child_node->symbol == CMD_SUFFIX)
			argv[i++] = ft_strdup(token->value);
		free_ast_node(child_node);
		child_list = child_list->next;
	}
#ifdef PIPE_DEBUG
	dprintf(2, "Sending the following into exec :\n");
	for (int j = 0; argv[j] ; j++)
dprintf(2, "argv["YEL"%d"RESET"] = "MAG"#"CYN"%s"MAG"#\n"RESET, j, argv[j]);
#endif
	exec(singleton_env(), argv, head);
	/* dprintf(2, BLU"Finished executing command %s %s\n"RESET, argv[0], argv[1]);//			REMOVE */		
	free(argv);
	close_redir(redir_stack);
	if (head->middle)
	{
#ifdef PIPE_DEBUG
		dprintf(2, "When executing, head->middle : %s\n" ,(head->middle->data) ? "On pipe" : "Not on pipe");
		dprintf(2, "Advancing\n");//			REMOVE		
#endif
		head->middle = head->middle->next;
#ifdef PIPE_DEBUG
		dprintf(2, "After executing: %s\n" ,(head->middle && head->middle->data) ? "On pipe" : "Not on pipe");
#endif
	}
}
