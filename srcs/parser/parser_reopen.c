/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_reopen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:38 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:41 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "color.h"
#include <stdio.h>
#include "exec.h"

int				check_reopen(t_ast_lst *ast_stack, t_list *token)
{
	int		reopen;

	(void)ast_stack;
	if ((reopen = ((t_token*)token->data)->id) == 666 || reopen == 42)
		return (PARSER_REOPEN);
	ft_dprintf(2, "42sh: parse error near `%s'\n", \
			((t_token*)token->data)->value);
	return (PARSER_ERROR);
}
