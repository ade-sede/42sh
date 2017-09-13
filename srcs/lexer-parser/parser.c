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
**	not hold a token. The function fill_simple_command takes the full
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
**			The function stops, and stack pointer goes back to ast_parse, bulding a
**			new branch for the new command, and attaching the simple command we
**			just created to a complexe one.
*/


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

t_ast			*start_complexe_command(t_ast *ast, t_list **token_list, \
		int *command_name)
{
	t_ast	*left_branch;
	t_ast	*right_branch;
	t_ast	*complexe_command;
	t_list	*child;

	/* Verify creation of the left branch happened */
	if (!(left_branch = ast))
	{
		ft_simple_lst_remove(token_list, NULL);
		dprintf(2, "Parse error near '%s'\n", (ast)->token->value);
		left_branch = flush_tree(left_branch);
		ast = flush_tree(ast);
	}
	child = ft_simple_lst_create(left_branch);

	/* Creating the new root */
	complexe_command = ast_create_node((t_token*)(*token_list)->data, NULL, COMPLEXE_COMMAND);
	ft_simple_lst_del_one(token_list, *token_list, NULL);

	/* Creating the right branch */
	right_branch = ast_create_node(NULL, NULL, SIMPLE_COMMAND);
	right_branch = fill_simple_command(right_branch, \
			token_list, command_name);

	/* Verify creation of the right branched happened */
	if (!right_branch)
	{
		if (ft_strequ((ast)->token->value, ";"))
			right_branch = flush_tree(right_branch);
		else if (!*token_list)
		{
			*token_list = reopen_command((ast)->token);
			right_branch = fill_simple_command(right_branch, \
					token_list, command_name);
		}
		else
		{
			ft_simple_lst_remove(token_list, NULL);
			dprintf(2, "Parse error near '%s'\n", (ast)->token->value);
			ast = flush_tree(ast);
			right_branch = flush_tree(right_branch);
		}
	}
	/* Push both branches as the child of the complexe commands */
	/* This should occure only if no error has been spotted */
	ft_simple_lst_pushback(&child, ft_simple_lst_create(right_branch));
	if (complexe_command)
		(complexe_command)->child = child;
	*command_name = 0;

	return (complexe_command);
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

t_ast			*ast_parse(t_ast *root, t_list **token_list, t_lst_head **head)
{
	int		command_name;
	t_token *token;
	int 	*p;
	t_pipe	*spipe;
	t_ast	*ast;

	ast = root;
	spipe = NULL;
	p = NULL;
	command_name = 0;
	if (token_list && *token_list)
	{
		token = (*token_list)->data;
		if (TK_IS_SEP(token->id))
		{
			if ((ast = start_complexe_command(ast, token_list, &command_name)) == NULL)
				return (NULL);
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
			if ((ast = create_simple_command(ast, token_list, &command_name)) == NULL)
					return (NULL);
		if (token_list && *token_list)
		{
			if ((ast = ast_parse(ast, token_list, head)) == NULL)
				return (NULL);
		}
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
	return (ast);
}

t_ast 	*create_simple_command(t_ast *ast, t_list **token_list, \
		int *command_name)
{
	ast = ast_create_node(NULL, NULL, SIMPLE_COMMAND);
	ast = fill_simple_command(ast, token_list, command_name);
	*command_name = 0;
	return (ast);
}

t_ast			*fill_simple_command(t_ast *simple_command, t_list **token_list, \
		int *command_name)
{
	t_ast	*new_node;
	t_token	*token;

	if (token_list && *token_list)
	{
		token = (*token_list)->data;
		if (TK_IS_SEP(token->id))
			return (simple_command);
		else
		{
			if (TK_IS_REDIR(token->id))
			{
				if (!(simple_command = append_redir(simple_command, token_list)))
					return (NULL);
			}
			else
			{
				new_node = ast_create_node_from_word(token_list, command_name);
				ft_simple_lst_pushback(&((simple_command)->child), \
						ft_simple_lst_create(new_node));
			}
			simple_command = fill_simple_command(simple_command, token_list, command_name);
		}
	}
	else
	{
		simple_command = flush_tree(simple_command);
	}
	return (simple_command);
}
