/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:39:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/19 14:30:34 by ade-sede         ###   ########.fr       */
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

/*
**	Receives an array containing the command name and its arguments.
*/

void	exec(t_env *env, const char **argv)
{
	size_t		index;

	index = 0;
	if (*argv != NULL)
	{
		if (!(exec_builtin(env, argv)))
			fork_exec_bin(env, argv);
	}
	else
		env->previous_exit = EXIT_FAILURE;
	while (argv[index] != NULL)
	{
		free((void*)(argv[index]));
		index++;
	}
}

/*
**	REPL. On this version, reading on static buff, or 4096.
*/

void	main_loop(t_env *env)
{
	t_ast		*ast;
	char		buff[LOCAL_BUFF_SIZE];
	t_lexer		lex;
	char		*nl;

	while (42)
	{
		put_prompt(env);
		ft_bzero(buff, LOCAL_BUFF_SIZE);
		read(0, buff, LOCAL_BUFF_SIZE);
		if ((nl = ft_strchr(buff, '\n')))
			*nl = '\0';
		if (*buff != 0)
		{
			lex = init_lexer(buff);
			ast = start_lex(&lex);
			exec_tree(ast);
		}
	}
}
