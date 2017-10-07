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
/* 	token_list = handle_lexer(&lex); */
/* 	new_command = ft_strchange(new_command, ft_strjoin(" ", new_command)); */
/* 	append_history(new_command); */
/* 	free(new_command); */
/* 	return (token_list); */
/* } */

int		abort_opening;
static t_ast	*create_right_branch(t_token *command_token, t_list **token_list, int *reopen)
{
	t_token		*token;
	t_ast		*right_branch;
	t_ast		*command_child;

	right_branch = create_simple_command(token_list);
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
//		reopen_line_editing(token_list, 0);
		*reopen = 1;
		return (NULL);
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
	cc = ast_create_node(token, NULL, COMPLEXE_COMMAND);
	if (!(right_branch = create_right_branch(cc->token, token_list, reopen)))
	{
		if (*reopen)
		{
			*reopen = token->id;
			dprintf(2, "reopen = token"MAG"#"CYN"%s"MAG"#\n"RESET, token->value);
		}
		cc = flush_tree(cc);
		left_branch = flush_tree(left_branch);
		return (NULL);
	}
	child = ft_simple_lst_create(left_branch);
	ft_simple_lst_pushback(&child, ft_simple_lst_create(right_branch));
	(cc)->child = child;
	return (cc);
}
