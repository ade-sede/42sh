/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:39:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/23 17:19:31 by ade-sede         ###   ########.fr       */
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

void	exec(t_env *env, const char **argv, t_lst_head *head)
{
	size_t		index;

	index = 0;
	if (*argv != NULL)
	{
		if (!(exec_builtin(env, argv)))
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

/*
**	REPL. On this version, reading on non-dynamic buff, 4096.
*/

void	main_loop(t_env *env)
{
	t_ast		*ast;
	char		buff[LOCAL_BUFF_SIZE];
	t_lexer		lex;
	char		*nl;
	t_lst_head	*head;

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
#ifdef PIPE_DEBUG
			dprintf(2, "Creating the initial empty node\n");//			REMOVE		
#endif
			head = ft_create_head(ft_double_lst_create(NULL));
			exec_tree(ast, head);
			ft_remove_head(&head, ft_free);
		}
	}
}
