#include "parser.h"
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

char	*construct_prompt(t_list	*ast_stack)
{
	t_token_id	token_id;
	char	*prompt;
	char	*token_prompt;
	t_list	*tmp;

	prompt = NULL;
	for (tmp = ast_stack; tmp; tmp = tmp->next)
	{
		token_id = -1;
		if (((t_ast *)tmp->data)->token)
			token_id = ((t_ast *)tmp->data)->token->id;
		if ((token_prompt = token_to_prompt(token_id)))
		{
			if (!prompt)
				prompt = ft_strdup(token_prompt);
			else
				prompt = ft_strjoin3_free(token_prompt, " ", prompt, 1);
		}
	}
	prompt = ft_strjoin_free(prompt, ">", 2);
	printf("prompt: %s\n", prompt);
	return (prompt);
}

