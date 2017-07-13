/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 11:46:51 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/13 13:52:42 by ade-sede         ###   ########.fr       */
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

static void		exec_redir(t_ast *ast)
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
** 	---------------------------------------------------------
** 	Atm, word expansion takes place on step two.
*/

void	exec_simple_command(t_ast *ast)
{
	t_token	*token;
	t_ast	*child_node;
	t_list	*child_list;
	size_t	i;
	const char	**argv;
#ifdef EXEC_DEBUG
	size_t		debug_index = 0;
#endif

	argv = ft_memalloc(sizeof(*argv) * (4096));
#ifdef EXEC_DEBUG
	size_t	index = 0;
	printf(RED"Reading child of a simple command\n"RESET);
#endif
	i = 0;
	child_list = ast->child;
	while (child_list)
	{
		child_node = child_list->data;
		token = child_node->token;
#ifdef EXEC_DEBUG
		printf("Child nb "BLU"[%zu]\n"RESET, index);
		index++;
		if (token && token->value)
			printf(PNK"Token's value : "MAG"#"CYN"%s"MAG"#"RESET, token->value);
		printf(YEL"(%d)"RESET"\n", child_node->symbol);
#endif
		if (child_node->symbol == IO_REDIRECT)
			exec_redir(child_node);
		if (child_node->symbol == CMD_NAME || child_node->symbol == CMD_SUFFIX)
		{
#ifdef EXEC_DEBUG
			printf(MAG"Adding to argv !!!\n"RESET);
#endif
			exec_expand(token);
			argv[i] = ft_strdup(token->value);
			i++;;
		}
		free_ast_node(child_node);
		child_list = child_list->next;
	}
#ifdef EXEC_DEBUG
	while (argv[debug_index] != NULL)
	{
		printf(RED"Printing content of argv\n"RESET);
		printf(GRN"Argv[%zu] = "MAG"#"CYN"%s"MAG"#\n"RESET, debug_index, argv[debug_index]);
		debug_index++;
	}
#endif
	exec(singleton_env(), argv);
	free(argv);
}
