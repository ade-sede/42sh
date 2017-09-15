/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 22:41:03 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/15 22:46:48 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include "env.h"
#include "exec.h"
#include "builtin.h"
#include "color.h"
#include "line_editing.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <errno.h>
#include <signal.h>

/*
** 	List of pipes should be generated during parsing and creation of the tree.
*/

static int	exec_pipe(t_ast *ast, t_lst_head *head)
{
	if (exec_tree(ast->child->data, head) == 0)
		exec_tree(ast->child->next->data, head);
	return (0);
}

/*
**	The first time exec_tree is called, we give it our root node as an
**	argument. Depending on the node symbol, it will start the execution of the
**	various commands.
*/

int			exec_tree(t_ast *ast, t_lst_head *head)
{
	t_token		*token;

	token = NULL;
	if (ast)
	{
		if (ast->symbol == SIMPLE_COMMAND)
		{
			check_pipes(ast, head);
			if (head->middle)
				head->middle = head->middle->next;
		}
		else if (ast->symbol == COMPLEXE_COMMAND)
		{
			token = ast->token;
			if (ft_strequ(token->value, "|"))
				return (exec_pipe(ast, head));
			else if (ft_strequ(token->value, ";"))
				return (semi_colon(ast, head));
			else if (ft_strequ(token->value, "&&"))
				return (logical_and(ast, head));
			else if (ft_strequ(token->value, "||"))
				return (logical_or(ast, head));
		}
		if (ast)
			return (0);
	}
	return (1);
}
