/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_compound_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:07 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*
**	compound_command : brace_group
**	                 | subshell
**	                 | for_clause
**	                 | case_clause
**	                 | if_clause
**	                 | while_clause
**	                 | until_clause
*/

int		exec_compound_command(t_ast *ast)
{
	int		status;

	status = exec(ast->child[0]);
	return (status);
}
