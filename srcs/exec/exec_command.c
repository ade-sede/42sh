/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 12:38:09 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/12 10:51:27 by ade-sede         ###   ########.fr       */
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

void	exec_simple_command(t_ast *ast, const char **argv)
{
	t_token	*token;
	t_ast	*child_node;
	t_list	*child_list;
#ifdef EXEC_DEBUG
	size_t	index = 0;
	printf(RED"Reading child of a simple command\n"RESET);
#endif

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
		if (child_node->symbol == CMD_NAME || child_node->symbol == CMD_SUFFIX)
		{
#ifdef EXEC_DEBUG
			printf(MAG"Adding to argv !!!\n"RESET);
#endif
			exec_expand(token);
			*argv = ft_strdup(token->value);
			argv++;
		}
		free_ast_node(child_node);
		child_list = child_list->next;
	}
}
