/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and_or.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:06 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*
**	and_or           :                         pipeline
**	                 | and_or AND_IF linebreak pipeline
**	                 | and_or OR_IF  linebreak pipeline
*/

int		exec_and_or(t_ast *ast)
{
	int		exit_status;

	if (ast->child[0] && !ast->child[3])
		return (exec(ast->child[0]));
	if (ast->child[0] && is_token(ast->child[1], TK_AND_IF) && ast->child[3])
	{
		if ((exit_status = exec(ast->child[0])) == EXIT_SUCCESS)
			return (exec(ast->child[3]));
		return (exit_status);
	}
	if ((exit_status = exec(ast->child[0])) != EXIT_SUCCESS)
		return (exec(ast->child[3]));
	return (exit_status);
}
