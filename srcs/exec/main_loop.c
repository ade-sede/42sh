/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:39:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/17 13:14:46 by ade-sede         ###   ########.fr       */
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
#ifdef NO_TERMCAPS
	char		buff[LOCAL_BUFF_SIZE];
#else
	char		*buff;
#endif
	t_lexer		lex;
	char		*nl;

#ifndef NO_TERMCAPS
	/*
	**	Init everything thats necessary. Might need to do that in an another fcts
	*/
	singleton_hist()->writen_buff = NULL;
	singleton_line()->len = 0;
	singleton_line()->pos = 0;
	singleton_line()->visu_mode = 0;
	singleton_line()->copied_text = NULL;
	singleton_line()->ws_col = get_ws_col();
	singleton_line()->buff = ft_strnew(4096);
#endif
	while (42)
	{
#ifdef NO_TERMCAPS
		put_prompt(env);
		ft_bzero(buff, LOCAL_BUFF_SIZE);
		read(0, buff, LOCAL_BUFF_SIZE);
#else
		singleton_line()->prompt_len = put_prompt(env);
		history_init(singleton_hist());
		edit_line_init(singleton_line());
		buff = edit_get_input(env);
#endif
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
