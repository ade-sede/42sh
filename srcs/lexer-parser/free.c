#include "libft.h"
#include "lexer.h"
#include "parser.h"
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
