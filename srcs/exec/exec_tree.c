/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 11:46:56 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/15 16:25:33 by ade-sede         ###   ########.fr       */
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

	if (ast)
	{
		child_list = ast->child;
		while (child_list)
		{
			child_node = child_list->data;
			flush_tree(child_node);
			child_list = child_list->next;
		}
		free_ast_node(ast);
	}
	return (NULL);
}

/*
**	Code to be executed if the complexe command is a logical and.
**	Must think about error handling in the parser/exec. (empty command for example)
*/

static void		logical_and(t_ast *ast)
{
	if (!ast->child->data)
		singleton_env()->previous_exit = EXIT_FAILURE;
	exec_tree(ast->child->data);
	if (singleton_env()->previous_exit == 0)
		exec_tree(ast->child->next->data);
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
			else if (ft_strequ(token->value, "&&"))
				logical_and(ast);
			else
				ast = flush_tree(ast);
		}
		if (ast)
			free_ast_node(ast);
	}
}
