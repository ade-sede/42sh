#include "libft.h"
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

void	exec_main_loop(t_ast *ast)
{
	singleton_jc()->background = 0;
	if (singleton_jc()->shell_is_interactive)
		conf_term_canonical();
	singleton_env()->previous_exit = exec(ast);
	if (singleton_jc()->shell_is_interactive)
		conf_term_non_canonical();
}

void	remove_lexer(t_lexer *lex)
{
	(void)lex;
	/* free_lexer(lex); */
	/* ft_strdel((char **)&lex->line); */
	/* ft_simple_lst_remove(&lex->stack, free_token); */
}

void	remove_parser(t_parser *parser)
{
	ft_genlst_remove(&parser->state_stack, NULL);
	ft_genlst_remove(&parser->ast_stack, free_ast_node);
}

void	quit_lex_and_parse(t_lexer *lex, t_parser *parser)
{
	if (!g_abort_opening && singleton_jc()->shell_is_interactive)
		history_append_command_to_list((char*)lex->line);
	remove_lexer(lex);
	remove_parser(parser);
}

void	lex_and_parse(t_ast *ast, char *buff)
{
	t_lexer		lexer;
	t_list		*token_list;
	int			res_lexer = -1;
	int			res_parser = -1;
	t_parser	parser;
	t_token		*reopen_token;

	init_lexer(&lexer, buff);
	init_parser(&parser);
	while (!((res_lexer == LEXER_SUCCESS && res_parser == PARSER_SUCCESS) || res_parser == PARSER_ERROR))
	{
		token_list = NULL;
		res_lexer = get_token_list(&lexer, &token_list, NULL);
		if (res_lexer == LEXER_REOPEN)
		{
			reopen_token = ft_memalloc(sizeof(*reopen_token) * 1);
			reopen_token->value = ft_strdup("quoted");
			reopen_token->state_info = NULL;
			reopen_token->delim = 0;
			reopen_token->id = 42;
			ft_simple_lst_pushback(&token_list, ft_simple_lst_create(reopen_token));
		}
		res_parser = parse(&parser, &ast, token_list);
		if (res_lexer == LEXER_REOPEN || res_parser == PARSER_REOPEN)
		{
			reopen_line_editing(&lexer, &parser);
			token_list = NULL;
			if (g_abort_opening)
				break ;
		}
	}
	if (res_parser == PARSER_SUCCESS && !g_abort_opening)
		exec_main_loop(ast);
	quit_lex_and_parse(&lexer, &parser);
}
