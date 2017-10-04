#include "line_editing.h"
#include "lexer.h"
#include "parser.h"
#include "color.h"
#include "libft.h"
#include "exec.h"
#include "failure.h"

/* static t_list	*reopen_command(void) */
/* { */
/* 	char	*new_command; */
/* 	t_list	*token_list; */
/* 	t_lexer	lex; */

/* 	load_prompt(singleton_env(), singleton_line(), "reopen_command", \ */
/* 			"command> "); */
/* 	new_command = ft_strdup(line_editing_get_input(singleton_line(), \ */
/* 			singleton_hist())); */
/* 	/1* new_command = ft_strchange(new_command, ft_strjoin(new_command, "\n")); *1/ */
/* 	lex = init_lexer(new_command); */
/* 	token_list = start_lex(&lex); */
/* 	new_command = ft_strchange(new_command, ft_strjoin(" ", new_command)); */
/* 	append_history(new_command); */
/* 	free(new_command); */
/* 	return (token_list); */
/* } */

t_ast			*create_right_branch(t_token *command_token, t_lexer *lex)
{
	t_token		*token;
	t_ast		*right_branch;
	t_ast		*command_child;

	right_branch = create_simple_command(lex);
	if (right_branch && right_branch->child)
	{
		command_child = right_branch->child->data;
		token = command_child->token;
	}
	else
	{
		investigate_error("Parse error near ", command_token->value, 0);
		return (flush_tree(right_branch));
	}
	if (!command_child || (token && token->id == TK_NEWLINE))
	{
		right_branch = flush_tree(right_branch);
		reopen_line_editing(lex, 0);
		right_branch = create_right_branch(command_token, lex);
	}
	return (right_branch);
}

t_ast			*start_complexe_command(t_ast *ast, t_lexer *lex)
{
	t_ast	*left_branch;
	t_ast	*right_branch;
	t_ast	*cc;
	t_token	*token;
	t_list	*child;

	token = start_lex(lex);
	ft_simple_lst_del_one(&lex->stack, lex->stack, NULL);
	if ((left_branch = ast) == NULL)
		return ((void*)(long)investigate_error("Parse error near", \
					token->value, 0));
	cc = ast_create_node(token, NULL, COMPLEXE_COMMAND);
	if (!(right_branch = create_right_branch(cc->token, lex)))
	{
		cc = flush_tree(cc);
		left_branch = flush_tree(left_branch);
		return (NULL);
	}
	child = ft_simple_lst_create(left_branch);
	ft_simple_lst_pushback(&child, ft_simple_lst_create(right_branch));
	(cc)->child = child;
	return (cc);
}
