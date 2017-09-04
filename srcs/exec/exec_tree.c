#include "libft.h"
#include <unistd.h>
#include "env.h"
#include "exec.h"
#include "builtin.h"
#include "line_editing.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>

/*
**	Delete the entire tree. Temporary to stop leaks.
*/

t_ast		*flush_tree(t_ast *ast)
{
	t_list	*child_list;
	t_ast	*child_node;

	if (ast)
	{
		child_list = ast->child;
		while (child_list)
		{
			child_node = child_list->data;
			if (child_node)
				flush_tree(child_node);
			child_list = child_list->next;
		}
		free_ast_node(ast);
	}
	return (NULL);
}

/*
**	Code to be executed if the complexe command is a logical and.  Must think
**	about error handling in the parser/exec. (empty command for example). Atm
**	we're changing the previous exit, but it might not be right.
*/

/*
**	Atm, error handling is poor. If an error is spotted, need to free the 2nd
**	node.
*/

static int	exec_pipe(t_ast *ast, t_lst_head *head)
{
	int			*p;

	p = palloc(sizeof(*p) * 2);
	pipe(p);
	ft_double_lst_add(&head, ft_double_lst_create(p));
	head->middle = head->first;
	if (exec_tree(ast->child->data, head) == 0)
		exec_tree(ast->child->next->data, head);
	else
	{
		ast->child->data = flush_tree(ast->child->next->data);
		head->middle = head->middle->next;
	}
return (0);
}

/*
**	The first time exec_tree is called, we give it our root node as an
**	argument. Depending on the node symbol, it will start the execution of the
**	various commands.
*/

int			end_branch(int error, t_ast *ast)
{
	ast = free_ast_node(ast);
	return (error);
}

int			exec_tree(t_ast *ast, t_lst_head *head)
{
	t_token		*token;

	token = NULL;
	if (ast)
	{
		if (ast->symbol == SIMPLE_COMMAND)
			exec_simple_command(ast, head);
		if (ast->symbol == COMPLEXE_COMMAND)
		{
			token = ast->token;
			if (ft_strequ(token->value, "|"))
				exec_pipe(ast, head);
			else if (ft_strequ(token->value, ";"))
				return (end_branch(semi_colon(ast, head), ast));
			else if (ft_strequ(token->value, "&&"))
				return (end_branch(logical_and(ast, head), ast));
			else if (ft_strequ(token->value, "||"))
				return (end_branch(logical_or(ast, head), ast));
		}
		if (ast)
			return (end_branch(0, ast));
	}
	return (1);
}
