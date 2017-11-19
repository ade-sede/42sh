#include "t_token.h"
#include "exec.h"
#include <stdio.h>

struct s_token_to_prompt	g_token_to_prompt[] =
{
	{TK_PIPE,"pipe"},
	{TK_AND_IF,"cmdand"},
	{TK_OR_IF,"cmdor"},
	{TK_IF, "if"},
	{TK_THEN,"then"},
	{TK_ELSE,"else"},
	{TK_ELIF,"elif"},
	{TK_CASE,"case"},
	{TK_WHILE,"while"},
	{TK_UNTIL,"until"},
	{TK_FOR,"for"},
	{TK_LBRACE,"cursh"},
	{TK_LPAREN,"subsh"},
	{-1, NULL},
};

char	*token_to_prompt(int token_id)
{
	int	i = 0;

	while (g_token_to_prompt[i].string)
	{
		if (token_id == g_token_to_prompt[i].id) 
			return (g_token_to_prompt[i].string);
		i++;
	}
	return (NULL);
}

char	*parser_construct_prompt(t_ast_lst	*ast_stack)
{
	int		token_id;
	int		token_next_id;
	char	*prompt;
	char	*token_prompt;
	t_ast_lst	*tmp;

	prompt = NULL;
	tmp = ast_stack;
	while (tmp)
	{
		token_id = -1;
//		printf("\n-----\n");
		if (tmp->ast->token)
		{
			token_id = tmp->ast->token->id;
//			debug_token(tmp->ast->token);
		}
		if (tmp->next && tmp->next->ast->token)
		{
			token_next_id = tmp->next->ast->token->id;
//			debug_token(tmp->next->ast->token);
		}
		if (token_id == TK_RPAREN && token_next_id == TK_LPAREN)
		{
			token_prompt = "function";
			tmp = tmp->next;
		}
		else 
			token_prompt = token_to_prompt(token_id);
		if (token_prompt)
		{
			if (!prompt)
				prompt = ft_strdup(token_prompt);
			else
				prompt = ft_strjoin3_free(token_prompt, " ", prompt, 1);
		}
		tmp = tmp->next;
	}
//	printf("prompt: %s\n", prompt);
	return (prompt);
}
