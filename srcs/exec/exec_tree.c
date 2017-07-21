/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 11:46:56 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/21 16:44:53 by ade-sede         ###   ########.fr       */
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
#include <stdio.h>
#include "printf.h"

/*
**	Delete the entire tree. Temporary to stop leaks.
*/

/* static t_ast	*flush_tree(t_ast *ast) */
/* { */
/* 	t_list	*child_list; */
/* 	t_ast	*child_node; */

/* 	if (ast) */
/* 	{ */
/* 		child_list = ast->child; */
/* 		while (child_list) */
/* 		{ */
/* 			child_node = child_list->data; */
/* 			flush_tree(child_node); */
/* 			child_list = child_list->next; */
/* 		} */
/* 		free_ast_node(ast); */
/* 	} */
/* 	return (NULL); */
/* } */

/*
**	Code to be executed if the complexe command is a logical and.  Must think
**	about error handling in the parser/exec. (empty command for example). Atm
**	we're changing the previous exit, but it might not be right.
*/

/*
**	Atm, error handling is poor. If an error is spotted, need to free the 2nd
**	node.
*/

static void		logical_and(t_ast *ast, t_lst_head *head)
{
	int		stop;


	stop = 0;
	if (!ast->child->data || !ast->child->next->data)
	{
		stop = 1;
		ft_dprintf(2, "Parse error near %s\n", ast->token->value);
	}
	ft_double_lst_add(&head, ft_double_lst_create(NULL));
#ifdef PIPE_DEBUG
				dprintf(2, "Creating 1 empty node\n");//			REMOVE		
#endif
	exec_tree(ast->child->data, head);
	if (singleton_env()->previous_exit == 0 && !stop)
		exec_tree(ast->child->next->data, head);
}

/*
**	The first time exec_tree is called, we give it our root node as an
**	argument. Depending on the node symbol, it will start the execution of the
**	various commands.
*/

void			exec_tree(t_ast *ast, t_lst_head *head)
{
	t_token		*token;
	int			*p;

	token = NULL;
	if (ast)
	{
		if (ast->symbol == SIMPLE_COMMAND)
			exec_simple_command(ast, head);
		if (ast->symbol == COMPLEXE_COMMAND)
		{
			token = ast->token;
			if (ft_strequ(token->value, "|"))
			{
				p = palloc(sizeof(*p) * 2);
				pipe(p);
#ifdef PIPE_DEBUG
				dprintf(2, "Creating 1 full node\n");//			REMOVE		
#endif
				ft_double_lst_add(&head, ft_double_lst_create(p));
				head->middle = head->first;
				exec_tree(ast->child->data, head);
				exec_tree(ast->child->next->data, head);
			}
			if (ft_strequ(token->value, ";"))
			{
				if (!ast->child->data || !ast->child->next->data)
					ft_dprintf(2, "Parse error near %s\n", token->value);
				ft_double_lst_add(&head, ft_double_lst_create(NULL));
#ifdef PIPE_DEBUG
				dprintf(2, "Creating 1 empty node\n");//			REMOVE		
#endif
				exec_tree(ast->child->data, head);
				exec_tree(ast->child->next->data, head);
			}
			else if (ft_strequ(token->value, "&&"))
				logical_and(ast, head);
			/* else */
			/* 	ast = flush_tree(ast); */
		}
		if (ast)
			free_ast_node(ast);
	}
}
