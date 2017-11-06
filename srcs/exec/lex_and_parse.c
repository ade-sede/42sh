#include "libft.h"
#include <unistd.h>
#include "env.h"
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
	//ft_strdel((char **)&lex->line);
	if (singleton_jc()->shell_is_interactive)
		conf_term_non_canonical();
	//ast = flush_tree(ast);
	//ft_simple_lst_remove(&lex->stack, free_token);
}

void	remove_lexer(t_lexer *lex)
{
	ft_strdel((char **)&lex->line);
	ft_simple_lst_remove(&lex->stack, free_token);
}

void	remove_parser(t_parser *parser)
{
	(void)parser;
	//free_ast(parser->ast);
}

void	quit_lex_and_parse(t_lexer *lex, t_parser *parser)
{
	if (!g_abort_opening)
		history_append_command_to_list((char*)lex->line);
	remove_lexer(lex);
	remove_parser(parser);
}

void	lex_and_parse(t_ast *ast, char *buff)
{
	t_lexer		lexer;
	t_list		*token_list;
	int			res_lexer;
	int			res_parser;
	t_parser	parser;
	t_token		*reopen_token;

	lexer = init_lexer(buff);
	init_parser(&parser);
	while (42)
	{
		token_list = NULL;
		res_lexer = lex_all(&lexer, &token_list);
		if (res_lexer > 0)
		{
			reopen_token = create_token(ft_strdup("quoted"), 0, 0);
			reopen_token->id = 42;
			ft_simple_lst_pushback(&token_list, ft_simple_lst_create(reopen_token));
		}
		res_parser = parse(&parser, &ast, token_list);
		if (res_parser == PARSER_ERROR)
			break ;
		if (res_lexer > 0 || res_parser == PARSER_REOPEN)
		{
			reopen_line_editing(&lexer, &parser, res_lexer);
			token_list = NULL;
			if (g_abort_opening)
				break ;
		}
		if (res_lexer == LEXER_SUCCESS && res_parser == PARSER_SUCCESS)
			break ;
	}
	if (res_parser == PARSER_SUCCESS && !g_abort_opening)
		exec_main_loop(ast);
	quit_lex_and_parse(&lexer, &parser);
}
