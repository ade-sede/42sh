/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_else_part.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:08 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*
**					  0       1             2        3         4
**	else_part        : Elif compound_list Then compound_list
**	                 | Elif compound_list Then compound_list else_part
**	                 | Else compound_list
*/

int		exec_else_part(t_ast *ast)
{
	if (is_token(ast->child[0], TK_ELIF))
	{
		if (exec(ast->child[1]) == EXIT_SUCCESS)
			return (exec(ast->child[3]));
		else if (ast->child[4])
			return (exec(ast->child[4]));
		return (EXIT_FAILURE);
	}
	else
		return (exec(ast->child[1]));
}
