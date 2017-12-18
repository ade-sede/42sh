/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:05 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "expand.h"
#include "t_line.h"
#include "exec_symbol.h"

/*
**	Check if exit job control.
**	return	: nb of exit main shell;
*/

int			parse_exit(t_ast *ast)
{
	int			i;
	int			ret;

	i = -1;
	ret = 0;
	if (!ast)
		return (0);
	while (ast->child[++i] && i < 7)
	{
		if (is_symb(ast, SUBSHELL) || is_symb(ast, SEPARATOR_OP)
			|| (is_symb(ast, PIPE_SEQUENCE) && ast->child[1]))
			return (0);
		else if (is_symb(ast, CMD_NAME))
		{
			if (!ft_strcmp(ast->child[0]->token->value, "exit"))
				return (++ret);
			else
			{
				singleton_jc()->warn_exit = 0;
				return (ret);
			}
		}
		ret += parse_exit(ast->child[i]);
	}
	return (ret);
}
