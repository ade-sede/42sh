/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_if_clause.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:09 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*
**					  0       1         2        3            4     5
** if_clause        : If compound_list Then compound_list else_part Fi
**					| If compound_list Then compound_list Fi
*/

int		exec_if_clause(t_ast *ast)
{
	if (exec(ast->child[1]) == EXIT_SUCCESS)
		return (exec(ast->child[3]));
	else if (ast->child[5])
		return (exec(ast->child[4]));
	return (EXIT_FAILURE);
}
