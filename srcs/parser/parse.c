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
**			The function stops, and stack pointer goes back to ast_parse,
**			bulding a new branch for the new command, and attaching the simple
**			command we just created to a complexe one.
*/

t_ast	*ast_parse(t_ast *root, t_lst_head **head, t_lexer *lex)
{
	t_token *token;
	t_ast	*ast;

	ast = root;
	if ((token = start_lex(lex)))
	{
		if (TK_IS_SEP(token->id))
		{
			if ((ast = start_complexe_command(ast, lex)) == NULL)
				return (NULL);
			if (add_pipe(token, head) == 0)
				return (flush_tree(ast));
		}
		else if ((ast = create_simple_command(lex)) == NULL)
			return (NULL);
		if ((ast = ast_parse(ast, head, lex)) == NULL)
			return (NULL);
	}
	else
		add_last_pipe(head);
	return (ast);
}
