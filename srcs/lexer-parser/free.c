/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 11:23:31 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/11 12:31:30 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>

void	free_token(t_token *token)
{
	free(token->value);
	free(token);
}

void	free_ast_node(t_ast *node)
{
	ft_simple_lst_remove(&node->child, NULL);
	if (node->token)
	{
		free_token(node->token);
	}
	free(node);
}
