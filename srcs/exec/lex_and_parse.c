#include "libft.h"
#include <unistd.h>
#include "env.h"
#include "exec.h"
#include "builtin.h"
#include "history.h"
#include "line_editing.h"
#include "lexer.h"
#include "parser.h"

void	exec_main_loop(t_lexer *lex, t_ast *ast, t_lst_head *head)
{
	history_append_command_to_list((char*)lex->line);
	conf_term_normal();
	exec_tree(ast, head);
	ft_strdel((char **)&lex->line);
	conf_term_canonical();
	ast = flush_tree(ast);
	if (head != NULL)
		ft_remove_head(&head, free_pipe);
	ft_simple_lst_remove(&lex->stack, free_token);
}

void	remove_lexer(t_lexer *lex)
{
	ft_strdel((char **)&lex->line);
	ft_simple_lst_remove(&lex->stack, free_token);
}

void	lex_and_parse(t_lst_head *head, t_ast *ast, char *buff)
{
	t_lexer		lex;
	t_list		*token_list;
	int			res_lexer;
	int			res_parser;

	lex = init_lexer(buff);
	while (42)
	{
		res_lexer = lex_all(&lex, &token_list, singleton_env()->alias);
		res_parser = ast_parse(&ast, &head, &token_list);
		if (res_parser == PARSER_ERROR)
			return (remove_lexer(&lex));
		if (res_lexer > 0 || TK_IS_REOPEN_SEP(res_parser))
		{
			reopen_line_editing(&lex, res_lexer, res_parser);
			ft_remove_head(&head, free_pipe);
			ast = flush_tree(ast);
			if (g_abort_opening)
				return (remove_lexer(&lex));
		}
		if (res_lexer == LEXER_SUCCESS && res_parser == PARSER_SUCCESS)
			break ;
	}
	exec_main_loop(&lex, ast, head);
}
