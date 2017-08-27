/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 04:40:02 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 04:48:53 by vcombey          ###   ########.fr       */
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
#include "printf.h"

/*
**	Delete the entire tree. Temporary to stop leaks.
*/

t_ast		*flush_tree(t_ast *ast)
{
	t_list	*child_list;
	t_ast	*child_node;

	if (ast)
	{
		child_list = ast->child;
		while (child_list)
		{
			child_node = child_list->data;
			if (child_node)
				flush_tree(child_node);
			child_list = child_list->next;
		}
		free_ast_node(ast);
	}
	return (NULL);
}

/*
**	Code to be executed if the complexe command is a logical and.  Must think
**	about error handling in the parser/exec. (empty command for example). Atm
**	we're changing the previous exit, but it might not be right.
*/

/*
**	Atm, error handling is poor. If an error is spotted, need to free the 2nd
**	node.
*/

static int		logical_or(t_ast *ast, t_lst_head *head)
{
	int		error;
	int		cmd1_exit;

	error = 0;
	cmd1_exit = 0;
	if (!ast->child->data || !ast->child->next->data)
	{
		error = 1;
		ft_dprintf(2, "Parse error near '%s'\n", ast->token->value);
	}
	if (!error)
	{
		ft_double_lst_add(&head, ft_double_lst_create(NULL));
		head->middle = head->first;
		exec_tree(ast->child->data, head);
		if ((cmd1_exit = singleton_env()->previous_exit) != 0)
			exec_tree(ast->child->next->data, head);
	}
	if (error != 0)
	{
		ft_dprintf(2, "error spotted\n");
		ast->child->data = flush_tree(ast->child->data);
		ast->child->next->data = flush_tree(ast->child->next->data);
	}
	if (cmd1_exit == 0)
		ast->child->next->data = flush_tree(ast->child->next->data);
	return ((cmd1_exit == 0 || error != 0) ? 1 : 0);
}

static int		semi_colon(t_ast *ast, t_lst_head *head)
{
	if (!ast->child->data)
		ft_dprintf(2, "Parse error near %s\n", ast->token->value);
	ft_double_lst_add(&head, ft_double_lst_create(NULL));
	head->middle = head->first;
	exec_tree(ast->child->data, head);
	exec_tree(ast->child->next->data, head);
	return (0);
}

static int		logical_and(t_ast *ast, t_lst_head *head)
{
	int		error;
	int		cmd1_exit;

	error = 0;
	cmd1_exit = 0;
	if (!(ast->child->data) || !(ast->child->next->data))
	{
		error = 1;
		ft_dprintf(2, "Parse error near '%s'\n", ast->token->value);
	}
	if (!error)
	{
		ft_double_lst_add(&head, ft_double_lst_create(NULL));
		head->middle = head->first;
		exec_tree(ast->child->data, head);
		if ((cmd1_exit = singleton_env()->previous_exit) == 0)
			exec_tree(ast->child->next->data, head);
	}
	if (error != 0)
	{
		ast->child->data = flush_tree(ast->child->data);
		ast->child->next->data = flush_tree(ast->child->next->data);
	}
	if (cmd1_exit != 0)
		ast->child->next->data = flush_tree(ast->child->next->data);
	return ((cmd1_exit != 0 || error != 0) ? 1 : 0);
}

static int		exec_pipe(t_ast *ast, t_lst_head *head)
{
	int			*p;
	int			error;

	error = 0;
	if (!(ast->child->data) || !(ast->child->next->data))
	{
		error = 1;
		ft_dprintf(2, "Parse error near '%s'\n", ast->token->value);
	}
	if (error == 0)
	{
		p = palloc(sizeof(*p) * 2);
		pipe(p);
		ft_double_lst_add(&head, ft_double_lst_create(p));
		head->middle = head->first;
		if (exec_tree(ast->child->data, head) == 0)
			exec_tree(ast->child->next->data, head);
		else
		{
			ast->child->data = flush_tree(ast->child->next->data);
			head->middle = head->middle->next;
		}
	}
	else
	{
		ast->child->data = flush_tree(ast->child->data);
		ast->child->next->data = flush_tree(ast->child->next->data);
	}
	return (0);
}

/*
**	The first time exec_tree is called, we give it our root node as an
**	argument. Depending on the node symbol, it will start the execution of the
**	various commands.
*/

int				end_branch(int error, t_ast *ast)
{
	ast = free_ast_node(ast);
	return (error);
}

int				exec_tree(t_ast *ast, t_lst_head *head)
{
	t_token		*token;

	token = NULL;
	if (ast)
	{
		if (ast->symbol == SIMPLE_COMMAND)
			exec_simple_command(ast, head);
		if (ast->symbol == COMPLEXE_COMMAND)
		{
			token = ast->token;
			if (ft_strequ(token->value, "|"))
				exec_pipe(ast, head);
			else if (ft_strequ(token->value, ";"))
				return (end_branch(semi_colon(ast, head), ast));
			else if (ft_strequ(token->value, "&&"))
				return (end_branch(logical_and(ast, head), ast));
			else if (ft_strequ(token->value, "||"))
				return (end_branch(logical_or(ast, head), ast));
		}
		if (ast)
			return (end_branch(0, ast));
	}
	return (1);
}
