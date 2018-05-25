/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_lexer_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:05 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "t_env.h"
#include "exec.h"
#include "builtin.h"
#include "history.h"
#include "line_editing.h"
#include "lexer.h"
#include "parser.h"
#include "job_control.h"
#include "parser.h"
#include "local.h"

void	remove_lexer(t_lexer *lex, t_list **token_list)
{
	free_lexer(lex);
	ft_simple_lst_remove(token_list, free_token);
}

void	remove_parser(t_parser *parser)
{
	ft_genlst_remove(&parser->state_stack, NULL);
	ft_genlst_remove(&parser->ast_stack, free_ast_node);
}
