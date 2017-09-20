#include "libft.h"
#include "failure.h"
#include "lexer.h"
#include "parser.h"
#include "exec.h"

/*
**	Creates an IO_REDIR node from 2 or 3 tokens. Returns this IO_REDIR node,
**	wich should be appended at the start of the command's child list.
**	The flag expected corresponds to what token the next part of the
**	redirection should be according to the one we just read.
**	1 = NAME
**	2 = REDIR
*/

static int	pushback_redir(t_list *child_list, t_list **token_list, \
		int expected)
{
	t_token	*token;

	while (token_list && *token_list && expected != 0)
	{
		token = (*token_list)->data;
		if (expected == 2)
		{
			ft_simple_lst_pushback(&child_list, \
				ft_simple_lst_create(ast_create_node(token, NULL, CMD_SUFFIX)));
		}
		if (expected == 1)
		{
			if (token->id != TK_NAME && token->id != TK_WORD)
				return (investigate_error("Parse error near ",  token->value, 0));
			ft_simple_lst_pushback(&child_list, \
				ft_simple_lst_create(ast_create_node(token, NULL, CMD_SUFFIX)));
		}
		ft_simple_lst_del_one(token_list, *token_list, NULL);
		--expected;
	}
	return (1);
}

t_ast		*ast_create_node_from_redir(t_list **token_list)
{
	t_list	*child_list;
	t_ast	*node;
	t_token	*token;
	int		expected;

	child_list = NULL;
	token = (*token_list)->data;
	if (token->id == TK_IO_NUMBER)
		expected = 2;
	else
		expected = 1;
	ft_simple_lst_pushback(&child_list, \
			ft_simple_lst_create(ast_create_node(token, NULL, CMD_SUFFIX)));
	ft_simple_lst_del_one(token_list, *token_list, NULL);
	node = ast_create_node(NULL, child_list, IO_REDIRECT);
	if ((pushback_redir(child_list, token_list, expected)) == 0)
		node = flush_tree(node);
	return (node);
}

t_ast		*append_redir(t_ast *root, t_list **token_list)
{
	t_ast	*new_node;

	new_node = ast_create_node_from_redir(token_list);
	ft_simple_lst_pushback(&(root->child), ft_simple_lst_create(new_node));
	if (!new_node)
		root = flush_tree(root);
	return (root);
}
