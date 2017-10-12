#include "libft.h"
#include <unistd.h>
#include "env.h"
#include "exec.h"
#include "builtin.h"
#include "history.h"
#include "line_editing.h"
#include "lexer.h"
#include "parser.h"

#ifdef PARSER_DEBUG
#include <stdio.h>
void	read_tree(t_ast *ast_start)
{
	size_t	index;
	t_token	*token_parent;
	char	*parent_name;
	t_list	*first_child;

	index = 0;
	token_parent = ast_start->token;
	printf(GRN"NODE = "RESET);
	if (token_parent)
		parent_name = token_parent->value;
	else
	{
		if (ast_start->symbol == SIMPLE_COMMAND)
			parent_name = "SIMPLE_COMMAND";
		if (ast_start->symbol == IO_REDIRECT)
			parent_name = "IO_REDIRECT";
	}
	printf(MAG"#"CYN"%s"MAG"#"RESET""YEL"(%d)\n"RESET, parent_name,
			ast_start->symbol);
	first_child = ast_start->child;
	while (first_child)
	{
		printf(RED"Starting treatment of child nb "BLU"%zu"RESET" of parent"
				MAG"#"CYN"%s"MAG"#"YEL"(%d)\n"RESET, index, parent_name, \
				ast_start->symbol);
		if (first_child->data)
			read_tree(first_child->data);
		printf(PNK"\nBACK TO PARENT -> "RESET"Current node = "CYN"%s"RESET" !!!\n",
				parent_name);
		first_child = first_child->next;
		index++;
	}
}
#endif

void	exec_main_loop(t_lexer *lex, t_ast *ast, t_lst_head *head)
{
	history_append_command_to_list((char*)lex->line);
#ifdef PARSER_DEBUG
	read_tree(ast);
#endif

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
		res_lexer = lex_all(&lex, &token_list);
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
