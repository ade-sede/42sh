/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 11:46:56 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/13 14:51:15 by ade-sede         ###   ########.fr       */
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
**	Delete the entire tree. Temporary to stop leaks.
*/

static t_ast	*flush_tree(t_ast *ast)
{
	t_list	*child_list;
	t_ast	*child_node;

	child_list = ast->child;
	while (child_list)
	{
		child_node = child_list->data;
		flush_tree(child_node);
		child_list = child_list->next;
	}
	free_ast_node(ast);
	return (NULL);
}

/*
**	The first time exec_tree is called, we give it our root node as an
**	argument. Depending on the node symbol, it will start the execution of the
**	various commands.
*/

void			exec_tree(t_ast *ast)
{
	t_token		*token;

	if (ast)
	{
		if (ast->symbol == SIMPLE_COMMAND)
			exec_simple_command(ast);
		if (ast->symbol == COMPLEXE_COMMAND)
		{
			token = ast->token;
			if (ft_strequ(token->value, ";"))
			{
				exec_tree(ast->child->data);
				exec_tree(ast->child->next->data);
			}
			else
				ast = flush_tree(ast);
		}
		if (ast)
			free_ast_node(ast);
	}
}
