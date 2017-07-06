/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:39:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/06 15:55:01 by ade-sede         ###   ########.fr       */
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
	t_token	*token;
	t_ast	*child_node;

	if (ast->symbol == SIMPLE_COMMAND)
	{
		while (ast->child)
		{
			child_node = ast->child->data;
			token = child_node->token;
#ifdef EXEC_DEBUG
			if (token && token->value)
			{
				printf("Token's value : "MAG"#"CYN"%s"MAG"#\n"RESET, token->value);
			}
			printf("Symbol "YEL"%d"RESET"\n", child_node->symbol);
#endif
			if (child_node->symbol == CMD_WORD)
			{
				word_expand(token);
				*argv = ft_strdup(token->value);
				argv++;
			}
			ast->child = ast->child->next;
		}
	}
}

void	exec(t_env *env, t_ast *ast)
{
	const char	**argv;

	argv = ft_memalloc(sizeof(*argv) * (4096));
	exec_tree(ast, argv);
	if (!(exec_builtin(env, argv)))
		fork_exec_bin(env, argv);
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
