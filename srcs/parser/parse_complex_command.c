#include "line_editing.h"
#include "lexer.h"
#include "parser.h"
#include "color.h"
#include "libft.h"
#include "exec.h"
#include "failure.h"

static t_ast	*create_right_branch(t_token *command_token, t_list **token_list, int *reopen)
{
	t_token		*token;
	t_ast		*right_branch;
	t_ast		*command_child;

	while (*token_list && ((t_token*)(*token_list)->data)->id == TK_NEWLINE)
		*token_list = (*token_list)->next;
	if (TK_IS_REOPEN_SEP(command_token->id) && (!*token_list))
	{
		*reopen = command_token->id;
		return (NULL);
	}
	right_branch = create_simple_command(token_list);
	if (right_branch && right_branch->child)
	{
		command_child = right_branch->child->data;
		token = command_child->token;
	}
	else if (command_token->id != TK_SEMI && command_token->id != TK_DSEMI)
	{
		investigate_error("Parse error near ", command_token->value, 0);
		*reopen = PARSER_ERROR;
		return (flush_tree(right_branch));
	}
	return (right_branch);
}

t_ast			*start_complexe_command(t_ast *ast, t_list **token_list, int *reopen)
{
	t_ast	*left_branch;
	t_ast	*right_branch;
	t_ast	*cc;
	t_token	*token;
	t_list	*child;

	token = *token_list ? (*token_list)->data : NULL;
	*token_list = *token_list ? (*token_list)->next : 0;
	if ((left_branch = ast) == NULL)
		return ((void*)(long)investigate_error("Parse error near", \
					token->value, 0));
	if (!(right_branch = create_right_branch(token, token_list, reopen)))
		return (flush_tree(left_branch)); //TODO: FRee ou pas Free
	cc = ast_create_node(token, NULL, COMPLEXE_COMMAND);
	child = ft_simple_lst_create(left_branch);
	ft_simple_lst_pushback(&child, ft_simple_lst_create(right_branch));
	(cc)->child = child;
	return (cc);
}
