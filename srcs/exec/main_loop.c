#include "libft.h"
#include <unistd.h>
#include "env.h"
#include "exec.h"
#include "builtin.h"
#include "line_editing.h"
#include "lexer.h"
#include "parser.h"
#define LOCAL_BUFF_SIZE 4096

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
	env_add_change(singleton_env(), "PS2", "dquote> ");
	env_add_change(singleton_env(), "PS3", "quote> ");
	line->size = BUFF_LINE_SIZE;
	line->put_prompt = &put_prompt;
}

char 	*line_editing_get_input(t_env *env, t_line *line, t_hist *hist)
{
	line->prompt_len = line->put_prompt(env);
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
		singleton_line()->put_prompt = &put_prompt;
		buff = line_editing_get_input(env, singleton_line(), singleton_hist());
#endif
		if ((nl = ft_strchr(buff, '\n')))
			*nl = '\0';
		if (*buff != 0)
		{
			lex = init_lexer(buff);
			ast = start_lex(&lex);
#ifdef PIPE_DEBUG
			dprintf(2, "Creating the initial empty node\n");//			REMOVE		
#endif
			head = ft_create_head(ft_double_lst_create(NULL));
			exec_tree(ast, head);
			ft_remove_head(&head, ft_free);
		}
	}
}
