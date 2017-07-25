#include "libft.h"
#include <unistd.h>
#include "env.h"
#include "exec.h"
#include "builtin.h"
#include "line_editing.h"
#include "lexer.h"
#include "parser.h"
#define LOCAL_BUFF_SIZE 4096



#ifdef PARSER_DEBUG
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
	printf(MAG"#"CYN"%s"MAG"#"RESET""YEL"(%d)\n"RESET, parent_name, ast_start->symbol);
	first_child = ast_start->child;
	while (first_child)
	{
		printf(RED"Starting treatment of child nb "BLU"%zu"RESET" of parent "MAG"#"CYN"%s"MAG"#"YEL"(%d)\n"RESET, index, parent_name, ast_start->symbol);
		if (first_child->data)
			read_tree(first_child->data);
		printf(PNK"\nBACK TO PARENT -> "RESET"Current node = "CYN"%s"RESET" !!!\n", parent_name);
		first_child = first_child->next;
		index++;
	}
}
#endif

/*
**	Receives an array containing the command name and its arguments.
*/

void	exec(t_env *env, const char **argv, t_lst_head *head)
{
	size_t		index;

	index = 0;
	if (*argv != NULL)
	{
		if (!(exec_builtin(env, argv, head)))
			fork_exec_bin(env, argv, head);
	}
	else
		env->previous_exit = EXIT_FAILURE;
	while (argv[index] != NULL)
	{
		free((void*)(argv[index]));
		index++;
	}
}


void	init_main_loop(t_line *line, t_hist *hist)
{	/*
	**	Init everything thats necessary. Might need to do that in an another fcts
	*/
	(void)hist;
	line->len = 0;
	line->pos = 0;
	line->visu_mode = 0;
	line->copied_text = NULL;
	line->ws_col = get_ws_col();
	line->buff = ft_strnew(BUFF_LINE_SIZE);
//	printf("\n, %s, \n", line->buff);
	env_add_change(singleton_env(), "PS1", "$> ");
	env_add_change(singleton_env(), "PS2", "dquote> ");
	env_add_change(singleton_env(), "PS3", "quote> ");
	line->size = BUFF_LINE_SIZE;
	load_prompt(singleton_env(), line, "PS1", "$> ");
}

char 	*line_editing_get_input(t_env *env, t_line *line, t_hist *hist)
{
	put_prompt(line);
	history_init(hist);
	edit_line_init(line);
	return (edit_get_input(env));
}

/*
**	REPL.
*/

void	main_loop(t_env *env)
{
	t_ast		*ast;
#ifdef NO_TERMCAPS
	char		buff[LOCAL_BUFF_SIZE];
#else
	char		*buff;
#endif
	t_lexer		lex;
	char		*nl;
	t_lst_head	*head;
	t_list		*token_list;

#ifndef NO_TERMCAPS
	init_main_loop(singleton_line(), singleton_hist());
#endif
	while (42)
	{
#ifdef NO_TERMCAPS
		put_prompt(env);
		ft_bzero(buff, LOCAL_BUFF_SIZE);
		read(0, buff, LOCAL_BUFF_SIZE);
#else
		load_prompt(singleton_env(), singleton_line(), "PS1", "$> ");
		buff = line_editing_get_input(env, singleton_line(), singleton_hist());
		history_refresh(buff);
#endif
		if ((nl = ft_strchr(buff, '\n')))
			*nl = '\0';
		if (*buff != 0)
		{
			lex = init_lexer(buff);
			token_list = start_lex(&lex);
#ifdef LEXER_DEBUG
			t_list	*token_debug = token_list;
			t_token *token;

			token = NULL;
			while (token_debug)
			{
				token = token_debug->data;
				dprintf(2, MAG"#"CYN"%s"MAG"#"YEL"(%d)\n"RESET,token->value, token->id);//			REMOVE		
				token_debug = token_debug->next;
			}
#endif
			ast = NULL;	// VERY IMPORTANT. Everything crash with a wrong init.
			ast = ast_parse(&ast, &token_list);
#ifdef PARSER_DEBUG
	read_tree(ast);
#endif
#ifdef PIPE_DEBUG
			dprintf(2, "Creating the initial empty node\n");//			REMOVE		
#endif
			head = ft_create_head(ft_double_lst_create(NULL));
			exec_tree(ast, head);
			ft_remove_head(&head, ft_free);
		}
	}
}
