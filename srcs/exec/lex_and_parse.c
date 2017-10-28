#include "libft.h"
#include <unistd.h>
#include "env.h"
#include "exec.h"
#include "builtin.h"
#include "history.h"
#include "line_editing.h"
#include "lexer.h"
#include "parser_slr.h"
#include "job_control.h"
#include "parser.h"


void	exec_main_loop(t_lexer *lex, t_ast *ast, t_job_control *jc)
{
	(void)jc;
	history_append_command_to_list((char*)lex->line);
	conf_term_normal();
	singleton_env()->previous_exit = exec(ast);
	//ft_strdel((char **)&lex->line);
	//do_job_notification(singleton_jc());
	conf_term_canonical();
	//ast = flush_tree(ast);
	//ft_simple_lst_remove(&lex->stack, free_token);
}
	

void	remove_lexer(t_lexer *lex)
{
	ft_strdel((char **)&lex->line);
	ft_simple_lst_remove(&lex->stack, free_token);
}

void	lex_and_parse(t_job_control *jc, t_ast *ast, char *buff)
{
	t_lexer		lex;
	t_list		*token_list;
	int			res_lexer;
	int			res_parser;
	t_token		*dollar_token;

	(void)jc;
	lex = init_lexer(buff);
	while (42)
	{
		res_lexer = lex_all(&lex, &token_list);
		dollar_token = create_token(ft_strdup("$"), 0, 0);
		dollar_token->id = $;
		ft_simple_lst_pushback(&token_list, ft_simple_lst_create(dollar_token));
		res_parser = parse(&ast, token_list);
		if (res_parser == PARSER_ERROR)
			return (remove_lexer(&lex));
		if (res_lexer > 0 || TK_IS_REOPEN_SEP(res_parser))
		{
			reopen_line_editing(&lex, res_lexer, res_parser);
			/* ast = flush_tree(ast); */
			if (g_abort_opening)
				return (remove_lexer(&lex));
		}
		if (res_lexer == LEXER_SUCCESS && res_parser == PARSER_SUCCESS)
			break ;
	}
	exec_main_loop(&lex, ast, jc);
}
