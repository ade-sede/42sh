/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_function_body.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:08 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*
** function_body    : compound_command
**                  | compound_command redirect_list
*/

int		exec_function_body(t_ast *ast)
{
	int		exit_status;
	t_list	*redirect_list;

	redirect_list = NULL;
	if (ast->child[1])
	{
		exec_redirect_list(ast->child[1], &redirect_list);
		exec_dup(redirect_list);
	}
	exit_status = exec(ast->child[0]);
	if (ast->child[1])
		close_dup(redirect_list);
	return (exit_status);
}
