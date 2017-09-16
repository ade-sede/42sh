/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_operator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 22:41:03 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/16 02:27:01 by vcombey          ###   ########.fr       */
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

int		logical_or(t_ast *ast, t_lst_head *head)
{
	int		error;
	int		cmd1_exit;

	error = 0;
	cmd1_exit = 0;
	exec_tree(ast->child->data, head);
	if ((cmd1_exit = singleton_env()->previous_exit) != 0)
		exec_tree(ast->child->next->data, head);
	if (cmd1_exit == 0)
		ast->child->next->data = flush_tree(ast->child->next->data);
	return ((cmd1_exit == 0 || error != 0) ? 1 : 0);
}

int		semi_colon(t_ast *ast, t_lst_head *head)
{
	if (!ast->child->data)
		return_failure("Parse error near ", ast->token->value);
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
	exec_tree(ast->child->data, head);
	if ((cmd1_exit = singleton_env()->previous_exit) == 0)
		exec_tree(ast->child->next->data, head);
	if (cmd1_exit != 0)
		ast->child->next->data = flush_tree(ast->child->next->data);
	return ((cmd1_exit != 0 || error != 0) ? 1 : 0);
}
