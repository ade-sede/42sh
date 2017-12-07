/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_and_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:04 by ade-sede         ###   ########.fr       */
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

static void		quit_lex_and_parse(t_lexer *lex, t_parser *parser, \
		t_list **token_list)
{
	(void)token_list;
	if (!g_abort_opening && singleton_jc()->shell_is_interactive)
		history_append_command_to_list((char*)lex->line);
	remove_lexer(lex, token_list);
	remove_parser(parser);
}

static void		lex_reopen(t_list **token_list)
{
	t_token		*reopen_token;

	reopen_token = ft_memalloc(sizeof(*reopen_token) * 1);
	reopen_token->value = ft_strdup("quoted");
	reopen_token->state_info = NULL;
	reopen_token->delim = 0;
	reopen_token->id = 42;
	ft_simple_lst_pushback(token_list,
			ft_simple_lst_create(reopen_token));
}

static t_list	*token_list(int res_l_and_p[0], t_lexer *lexer,
			t_ast **ast, t_parser *parser)
{
	t_list		*token_list_ret;

	token_list_ret = NULL;
	res_l_and_p[0] = get_token_list(lexer, &token_list_ret,
			singleton_env()->alias);
	if (res_l_and_p[0] == LEXER_REOPEN)
		lex_reopen(&token_list_ret);
	res_l_and_p[1] = parse(parser, ast, token_list_ret);
	return (token_list_ret);
}

static t_list	*init_sale(t_lexer *lexer, int *res, t_parser *parser, char *b)
{
	res[0] = -1;
	res[1] = -1;
	init_lexer(lexer, b);
	init_parser(parser);
	return (NULL);
}

int				lex_and_parse(t_ast *ast, char *buff, t_modes *modes)
{
	t_lexer		lexer;
	int			res_l_and_p[2];
	t_parser	parser;
	t_list		*big_list;

	big_list = init_sale(&lexer, res_l_and_p, &parser, buff);
	while (!((res_l_and_p[0] == LEXER_SUCCESS &&
	res_l_and_p[1] == PARSER_SUCCESS) || res_l_and_p[1] == PARSER_ERROR))
	{
		ft_simple_lst_pushback(&big_list, token_list(res_l_and_p, &lexer, &ast,
					&parser));
		if (res_l_and_p[0] == LEXER_REOPEN || res_l_and_p[1] == PARSER_REOPEN)
		{
			if (!reopen(&lexer, &parser, modes))
				return (0);
			if (g_abort_opening)
				break ;
		}
	}
	if (res_l_and_p[1] == PARSER_SUCCESS && !g_abort_opening)
		exec_main_loop(ast);
	else
		local_add_change_from_key_value(singleton_env(), "?", "127");
	quit_lex_and_parse(&lexer, &parser, &big_list);
	return ((res_l_and_p[1] == PARSER_ERROR && modes->mode > 0) ? 0 : 1);
}
