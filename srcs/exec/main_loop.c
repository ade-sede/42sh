#include "libft.h"
#include <unistd.h>
#include "env.h"
#include "exec.h"
#include "builtin.h"
#include "history.h"
#include "line_editing.h"
#include "lexer.h"
#include "parser.h"
#define LOCAL_BUFF_SIZE 4096

#ifdef PARSER_DEBUG
#include <stdio.h>
static void	read_tree(t_ast *ast_start)
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
		printf(PNK"\nBACK TO PARENT -> "RESET"Current node = "CYN"%s"RESET" !!!\n", parent_name);
		first_child = first_child->next;
		index++;
	}
}
#endif

/*
**	Receives an array containing the command name and its arguments, forwards
**	this array to the appropriate function then frees it.
*/
void	exec(t_env *env, const char **argv, t_lst_head *head)
{
	size_t		index;

	index = 0;
	if (*argv != NULL)
	{
		if (!(exec_builtin(env, argv, head)))
			fork_exec_bin(env, argv, head); }
	else
		env->previous_exit = EXIT_FAILURE;
	while (argv[index] != NULL)
	{
		free((void*)(argv[index]));
		index++;
	}
	free(argv);
}

void	init_main_loop(t_line *line, t_hist *hist)
{
	(void)hist;
	line->len = 0;
	line->pos = 0;
	line->visu_mode = 0;
	line->copied_text = NULL;
	line->ws_col = get_ws_col();
	line->buff = ft_strnew(BUFF_LINE_SIZE);
	env_add_change(singleton_env(), "PS1", "$> ");
	env_add_change(singleton_env(), "PS2", "dquote> ");
	env_add_change(singleton_env(), "PS3", "quote> ");
	line->size = BUFF_LINE_SIZE;
	load_prompt(singleton_env(), line, "PS1", "$> ");
	line->heredoc = 0;
	line->col_target = -1;
}

char	*line_editing_get_input(t_line *line, t_hist *hist, void (*sig_handler)(void))
{
	put_prompt(line);
	history_init(hist);
	edit_line_init(line, sig_handler);
	return (edit_get_input());
}
#include <stdio.h>
void	lex_and_parse(char *buff)
{
	t_lexer		lex;
	t_lst_head	*head;
	t_list		*token_list;
	t_ast		*ast;
	int			res_lexer;
	int			res_parser;
	int			done;

	ast = NULL;
	head = NULL;
	lex = init_lexer(buff);
	done = 0;
	while (!done)
	{
		res_lexer = lex_all(&lex, &token_list);
		res_parser = ast_parse(&ast, &head, &token_list);
/*
**			if (res_parser == PARSE_ERROR)
**				return ;
*/
			if (res_lexer == LEXER_REOPEN)
				//|| res_parser == REOPEN)
			{
				reopen_line_editing(&lex, 0);
				if (abort_opening)
					return ;
			}
			if (res_lexer == LEXER_SUCCESS)
			{
				printf("lex_and_parse done\n");
				done = 1;
			}
	}
	history_append_command_to_list((char*)lex.line);
#ifdef PARSER_DEBUG
	if (ast)
		read_tree(ast);
#endif
	conf_term_normal();
	exec_tree(ast, head);
	/*
**		if (lex.stack)
**			ft_simple_lst_remove(&lex.stack, free_token);
*/
	ft_strdel((char **)&lex.line);
	conf_term_canonical();
	ast = flush_tree(ast);
	if (head != NULL)
		ft_remove_head(&head, free_pipe);
	free(buff);
}

void	main_loop(t_env *env)
{
	char		*buff;

	init_main_loop(singleton_line(), singleton_hist());
	while (42)
	{
		load_prompt(env, singleton_line(), "PS1", "$> ");
		buff = ft_strdup(line_editing_get_input(singleton_line(), \
					singleton_hist(), &edit_set_signals_open));
		if (*buff != 0)
			lex_and_parse(buff);
		else
			free(buff);
	}
}
