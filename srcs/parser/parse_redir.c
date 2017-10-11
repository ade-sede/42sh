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

/*
**	Getting input for heredoc tokens
*/

static char	*get_heredoc_input(char *value)
{
	char	*buff;
	char	*cat;
	char	*target;

	target = ft_strjoin(value, "\n");
	singleton_line()->heredoc = 1;
	load_prompt(singleton_env(), singleton_line(), \
			"heredoc", "heredoc> ");
	cat = ft_strnew(0);
	while (1)
	{
		buff = line_editing_get_input(singleton_line(), singleton_hist(), &edit_set_signals_reopen);
		if (ft_strequ(buff, target) || ft_strchr(buff, 4))
			break ;
		cat = ft_strchange(cat, ft_strjoin(cat, buff));
	}
	singleton_line()->heredoc = 0;
	free(target);
	return (cat);
}

static int	pushback_redir(t_list *child_list, int expected, t_list **token_list, int heredoc)
{
	t_token	*token;
	t_ast	*heredoc_node;

	while ((token = (*token_list)->data) && expected != 0)
	{
		if (expected == 2)
		{
			ft_simple_lst_pushback(&child_list, ft_simple_lst_create(ast_create_node(token, NULL, CMD_SUFFIX)));
			if (token->id == TK_HERE)
				heredoc = TRUE;
		}
		if (expected == 1)
		{
			if (token->id != TK_NAME && token->id != TK_WORD)
				return (investigate_error(NULL, "Parse error near ",  token->value, 0));
			ft_simple_lst_pushback(&child_list, \
					ft_simple_lst_create(ast_create_node(token, NULL, CMD_SUFFIX)));
			if (heredoc)
			{
				heredoc_node = (ft_last_simple_lst(child_list))->data;
				heredoc_node->heredoc_content = get_heredoc_input(token->value);
			}
		}
		*token_list = *token_list ? (*token_list)->next : 0;
		--expected;
	}
	if (expected != 0)
		return (investigate_error(NULL, "Parse error near ",  token->value, 0));
	return (1);
}

static t_ast		*ast_create_node_from_redir(t_token *token, t_list **token_list)
{
	t_list	*child_list;
	t_ast	*node;
	int		expected;
	int		heredoc;

	heredoc = FALSE;
	child_list = NULL;
	if (token->id == TK_IO_NUMBER)
		expected = 2;
	else
	{
		if (token->id == TK_HERE)
			heredoc = TRUE;
		expected = 1;
	}
	ft_simple_lst_pushback(&child_list, \
			ft_simple_lst_create(ast_create_node(token, NULL, CMD_SUFFIX)));
	node = ast_create_node(NULL, child_list, IO_REDIRECT);
	*token_list = *token_list ? (*token_list)->next : 0;
	if ((pushback_redir(child_list, expected, token_list, heredoc)) == 0)
		node = flush_tree(node);
	return (node);
}

t_ast		*append_redir(t_ast *root, t_token *token, t_list **token_list)
{
	t_ast	*new_node;

	new_node = ast_create_node_from_redir(token, token_list);
	ft_simple_lst_pushback(&(root->child), ft_simple_lst_create(new_node));
	if (!new_node)
		root = flush_tree(root);
	return (root);
}
