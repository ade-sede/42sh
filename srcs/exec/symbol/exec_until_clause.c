/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_until_clause.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:10 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*
** until_clause     : Until compound_list do_group
*/

int		exec_until_clause(t_ast *ast)
{
	while (exec(ast->child[1]) != EXIT_SUCCESS && !g_abort_opening)
		exec(ast->child[2]);
	return (EXIT_SUCCESS);
}
