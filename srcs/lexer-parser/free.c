#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "exec.h"
#include <stdio.h>

void	free_token_list(t_list *token_list)
{
	t_list	*tmp;

	while (token_list)
	{
		tmp = token_list->next;
		free_token(token_list->data);
		free(token_list);
		token_list = tmp;
	}
}

void	free_token(void *value)
{
	t_token *token;

	token = (t_token*)value;
	if (token->value)
		free(token->value);
	free(token);
}

t_ast	*free_ast_node(t_ast *node)
{
	if (node)
	{
		ft_simple_lst_remove(&node->child, NULL);
		if (node->token)
			free_token(node->token);
		free(node);
	}
	return (NULL);
}

/*
**	Deletes the entire tree, from the given node to the last leaf
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

void		free_pipe(void *pipe)
{
	t_pipe *a;

	a = (t_pipe*)pipe;
	if (a)
	{
		free(a->p);
		free(a);
	}
}
