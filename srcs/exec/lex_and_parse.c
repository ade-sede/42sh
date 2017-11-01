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

void	exec_main_loop(t_lexer *lex, t_ast *ast)
{
	history_append_command_to_list((char*)lex->line);
	if (singleton_jc()->shell_is_interactive)
		conf_term_canonical();
	singleton_env()->previous_exit = exec(ast);
	//ft_strdel((char **)&lex->line);
	do_job_notification(singleton_jc());
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

void	lex_and_parse(t_ast *ast, char *buff)
{
	t_lexer		lex;
	t_list		*token_list;
	int			res_lexer;
	int			res_parser;
	t_parser	parser;

	lex = init_lexer(buff);
	init_parser(&parser);
	while (42)
	{
		res_lexer = lex_all(&lex, &token_list);
		res_parser = parse(&parser, &ast, token_list);
		if (res_parser == PARSER_ERROR)
			return (remove_lexer(&lex));
		if (res_lexer > 0 || res_parser == PARSER_REOPEN)
		{
			reopen_line_editing(&lex, &parser, res_lexer);
			if (g_abort_opening)
				return (remove_lexer(&lex));
		}
		if (res_lexer == LEXER_SUCCESS && res_parser == PARSER_SUCCESS)
			break ;
	}
	exec_main_loop(&lex, ast);
}
