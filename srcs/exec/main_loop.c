/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:39:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/12 16:20:02 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include "env.h"
#include "exec.h"
#include "builtin.h"
#include "line_editing.h"
#include "lexer.h"
#include "parser.h"
#define LOCAL_BUFF_SIZE 4096

void	exec_tree(t_ast *ast, const char **argv)
{
	if (ast)
	{
	if (ast->symbol == SIMPLE_COMMAND)
		exec_simple_command(ast, argv);
	free_ast_node(ast);
	}
}

void	exec(t_env *env, t_ast *ast)
{
	const char	**argv;
	size_t		index;
#ifdef EXEC_DEBUG
	size_t		debug_index = 0;
#endif

	index = 0;
	argv = ft_memalloc(sizeof(*argv) * (4096));
	exec_tree(ast, argv);
#ifdef EXEC_DEBUG
	while (argv[debug_index] != NULL)
	{
		printf(RED"Printing content of argv\n"RESET);
		printf(GRN"Argv[%zu] = "MAG"#"CYN"%s"MAG"#\n"RESET,debug_index, argv[debug_index]);
		debug_index++;
	}
#endif
	if (*argv != NULL)
	{
	if (!(exec_builtin(env, argv)))
		fork_exec_bin(env, argv);
	}
	while (argv[index] != NULL)
	{
		free((void*)(argv[index]));
		index++;
	}
	free(argv);
}

void	main_loop(t_env *env)
{
	t_ast		*ast;
	char		buff[4096];
	t_lexer		lex;

	while (42)
	{
		put_prompt(env);
		ft_bzero(buff, LOCAL_BUFF_SIZE);
		read(0, buff, LOCAL_BUFF_SIZE);
		*ft_strchr(buff, '\n') = '\0';
		if (*buff != 0)
		{
			lex = init_lexer(buff);
			ast = start_lex(&lex);
			exec(env, ast);
		}
	}
}
