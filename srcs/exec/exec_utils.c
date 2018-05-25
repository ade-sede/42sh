/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:00 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int		is_token(t_ast *ast, int token_id)
{
	if (ast && ast->token && ast->token->id == token_id)
		return (1);
	return (0);
}

int		is_symb(t_ast *ast, int symbol)
{
	if (ast && ast->symbol == symbol)
		return (1);
	return (0);
}
