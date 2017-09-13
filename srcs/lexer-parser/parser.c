#include "line_editing.h"
#include "lexer.h"
#include "parser.h"
#include "color.h"
#include "libft.h"
#include "exec.h"
#include "printf.h"

/*
**	As a token is considered to be a leaf of the tree, the tree is being built
**	from the leaves to the root. Upon reading, tokens are converted into the
**	AST's nodes. Some nodes merely represent a symbol from our grammar, and do
**	not hold a token. The function ast_create_simple_command takes the full
**	list of tokens, and a temporary root to build upon. This temporary root is
**	considered to be a `simple command'.  The function will create a node, that
**	will act as a temporary root for our tree. For each token it reads from the
**	list:
**	- If the token is a WORD (not an operator ?)
**
**		A node will be created from that token by the function
**		ast_create_node_from_word. The node's symbol should be determined
**		according to the POSIX STANDARD's rules. This node will then be
**		appended to the child list of the current root node.
**
**	- If the token is an operator
**		- If the token is a redirection / an IO_NUMBER
**
**			A node representing an IO_REDIRECT should be created from every
**			token belonging to the redirection. This node will not hold any
**			token and will then be appended to the child list of the
**			current root node.
**
**		- If the token is a separator
**
**			The function stops, and stack goes back to ast_parse, bulding a
**			new branch for the new command, and attaching the simple command we
**			just created to a complexe one.
*/

static void		start_simple_command(t_ast **root, t_list **token_list, \
		int *command_name)
{
	*root = ast_create_node(NULL, NULL, SIMPLE_COMMAND);
	*root = ast_create_simple_command(root, token_list, command_name);
	*command_name = 0;
}

static t_list	*reopen_command(t_token *token)
{
#ifndef NO_TERMCAPS
	char	*new_command;
#else
	char	new_command[4096];
#endif
	t_list	*token_list;
	t_lexer	lex;

	(void)token;
#ifndef NO_TERMCAPS
	load_prompt(singleton_env(), singleton_line(), "reopen_command", \
			"command> ");
	new_command = line_editing_get_input(singleton_env(), singleton_line(), \
			singleton_hist());
#else
	bzero(new_command, 4096);
	read(0, new_command, 4096);
	*strchr(new_command, '\n') = 0;
#endif
	lex = init_lexer(new_command);
	token_list = start_lex(&lex);
	return (token_list);
}

/*
**	Sometimes the token might represent a complexe command, but there was no
**	initial simple command or nothing to build a new one. In this case, the
**	corresponding child has a NULL ast.
*/

static void		start_complexe_command(t_ast **root, t_list **token_list, \
		int *command_name, t_token *token)
{
	t_ast	*left_branch;
	t_ast	*new_branch_root;
	t_list	*child;

	left_branch = *root;
	child = ft_simple_lst_create(*root);
	*root = ast_create_node(token, NULL, COMPLEXE_COMMAND);
	ft_simple_lst_del_one(token_list, *token_list, NULL);
	new_branch_root = ast_create_node(NULL, NULL, SIMPLE_COMMAND);
	new_branch_root = ast_create_simple_command(&new_branch_root, \
			token_list, command_name);
	if (!left_branch || (left_branch && !left_branch->child))
	{
		ft_simple_lst_remove(token_list, NULL);
		dprintf(2, "Parse error near '%s'\n", (*root)->token->value);
		left_branch = flush_tree(left_branch);
		*root = flush_tree(*root);
	}
	else if (!new_branch_root->child)
	{
		if (ft_strequ((*root)->token->value, ";"))
			new_branch_root = flush_tree(new_branch_root);
		else if (!*token_list)
		{
			*token_list = reopen_command((*root)->token);
			new_branch_root = ast_create_simple_command(&new_branch_root, \
					token_list, command_name);
		}
		else
		{
			ft_simple_lst_remove(token_list, NULL);
			dprintf(2, "Parse error near '%s'\n", (*root)->token->value);
			*root = flush_tree(*root);
			new_branch_root = flush_tree(new_branch_root);
		}
	}
	ft_simple_lst_pushback(&child, ft_simple_lst_create(new_branch_root));
	if (*root)
		(*root)->child = child;
	*command_name = 0;
}



t_pipe	*create_pipe(int *p)
{
	t_pipe	*new;

	if (!p)
		return (NULL);
	new = ft_memalloc(sizeof(*new));
	new->p = p;
	return (new);
}

/*
**	This function starts the creation of the tree's branch.
*/

t_ast			*ast_parse(t_ast **root, t_list **token_list, t_lst_head **head)
{
	int		command_name;
	t_token *token;
	int 	*p;
	t_pipe	*spipe = NULL;
	p = NULL;
	command_name = 0;
	if (token_list && *token_list)
	{
		token = (*token_list)->data;
		if (TK_IS_SEP(token->id))
		{
			start_complexe_command(root, token_list, &command_name, token);
			if (ft_strequ(token->value, "|"))
			{
				p = palloc(sizeof(*p) * 2);
				pipe(p);
			}
			spipe = create_pipe(p);
			if (*head == NULL)
				*head = ft_create_head(ft_double_lst_create(spipe));
			else
				ft_double_lst_pushback(head, ft_double_lst_create(spipe));
		}
		else
			start_simple_command(root, token_list, &command_name);
		if (token_list && *token_list)
			ast_parse(root, token_list, head);
		else
		{
			spipe = NULL;
			if (*head == NULL)
				*head = ft_create_head(ft_double_lst_create(spipe));
			else
			{
				ft_double_lst_pushback(head, ft_double_lst_create(NULL));
				(*head)->middle = (*head)->first;
			}
		}
	}
	return (*root);
}

t_ast			*ast_create_simple_command(t_ast **root, t_list **token_list, \
		int *command_name)
{
	t_ast	*new_node;
	t_token	*token;

	if (token_list && *token_list)
	{
		token = (*token_list)->data;
		if (TK_IS_SEP(token->id))
			return (*root);
		else
		{
			if (TK_IS_REDIR(token->id))
				append_redir(root, token_list);
			else
			{
				new_node = ast_create_node_from_word(token_list, command_name);
				ft_simple_lst_pushback(&((*root)->child), \
						ft_simple_lst_create(new_node));
			}
			*root = ast_create_simple_command(root, token_list, command_name);
		}
	}
	return (*root);
}
