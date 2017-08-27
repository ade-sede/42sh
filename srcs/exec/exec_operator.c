/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_operator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 10:33:23 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 12:48:57 by vcombey          ###   ########.fr       */
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

int		logical_or(t_ast *ast, t_lst_head *head)
{
	int		error;
	int		cmd1_exit;

	error = 0;
	cmd1_exit = 0;
	if (!ast->child->data || !ast->child->next->data)
	{
		error = 1;
		return_failure("Parse error near ", ast->token->value);
		ast->child->data = flush_tree(ast->child->data);
		ast->child->next->data = flush_tree(ast->child->next->data);
	}
	else
	{
		ft_double_lst_add(&head, ft_double_lst_create(NULL));
		head->middle = head->first;
		exec_tree(ast->child->data, head);
		if ((cmd1_exit = singleton_env()->previous_exit) != 0)
			exec_tree(ast->child->next->data, head);
	}
	if (cmd1_exit == 0)
		ast->child->next->data = flush_tree(ast->child->next->data);
	return ((cmd1_exit == 0 || error != 0) ? 1 : 0);
}

int		semi_colon(t_ast *ast, t_lst_head *head)
{
	if (!ast->child->data)
		return_failure("Parse error near ", ast->token->value);
	ft_double_lst_add(&head, ft_double_lst_create(NULL));
	head->middle = head->first;
	exec_tree(ast->child->data, head);
	exec_tree(ast->child->next->data, head);
	return (0);
}

int		logical_and(t_ast *ast, t_lst_head *head)
{
	int		error;
	int		cmd1_exit;

	error = 0;
	cmd1_exit = 0;
	if (!(ast->child->data) || !(ast->child->next->data))
	{
		error = 1;
		return_failure("Parse error near ", ast->token->value);
		ast->child->data = flush_tree(ast->child->data);
		ast->child->next->data = flush_tree(ast->child->next->data);
	}
	else
	{
		ft_double_lst_add(&head, ft_double_lst_create(NULL));
		head->middle = head->first;
		exec_tree(ast->child->data, head);
		if ((cmd1_exit = singleton_env()->previous_exit) == 0)
			exec_tree(ast->child->next->data, head);
	}
	if (cmd1_exit != 0)
		ast->child->next->data = flush_tree(ast->child->next->data);
	return ((cmd1_exit != 0 || error != 0) ? 1 : 0);
}
