#include "t_ast.h"
#include "t_token.h"
#include "libft.h"

/*
**	Creates a node of the AST, giving the address of the first child of its
**	list of childs.
*/

t_ast	*ast_create_node(t_token *token, t_list *child, t_symbol symbol)
{
	t_ast	*node;

	node = palloc(sizeof(*node));
	node->child = child;
	node->token = token;
	node->symbol = symbol;
	node->heredoc_content = NULL;
	return (node);
}

/*
**	Frees one node of the ast : The list of childs, and the token it contains
**	and the structure itself.
*/

t_ast	*free_ast_node(t_ast *node)
{
	if (node)
	{
		ft_simple_lst_remove(&node->child, NULL);
//		if (node->token)
//			free_token(node->token);
		free(node);
	}
	return (NULL);
}

/*
**	Deletes the entire tree, from the given node to the last leaf
*/

t_ast	*flush_tree(t_ast *ast)
{
	t_list	*child_list;
	t_ast	*child_node;

	if (ast)
	{
		if (ast->heredoc_content)
			free(ast->heredoc_content);
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
