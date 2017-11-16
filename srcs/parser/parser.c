#include "parser.h"
#include "color.h"
#include <stdio.h>

void	debug_pstate(t_listint *stack)
{
	t_listint	*tmp;

	printf("state_stack: ");
	for (tmp = stack; tmp; tmp = tmp->next)
		printf("%d ", tmp->data);
	printf("\n");
}
#include "exec.h"
void	debug_ast_stack(t_list *ast_stack)
{
	t_list	*tmp;

	printf("state_stack: \n");
	for (tmp = ast_stack; tmp; tmp = tmp->next)
		debug_symbol(tmp->data);
	printf("\n");
}

int		check_reopen(t_ast_lst *ast_stack, t_list *token)
{
	(void)ast_stack;
	int		reopen;

	if ((reopen = ((t_token*)token->data)->id ) == 666 || reopen == 42 || reopen == 6)
		return (PARSER_REOPEN);
	dprintf(2, "42sh: parse error near `%s' [%d]\n", ((t_token*)token->data)->value, reopen);
	return (PARSER_ERROR);
}

t_state_lst		*state_lst_new(int n)
{
	t_state_lst *new;

	new = ft_memalloc(sizeof(t_state_lst));
	new->state = n;
	return (new);
}

t_ast_lst		*ast_lst_new(t_ast *ast)
{
	t_ast_lst *new;

	new = ft_memalloc(sizeof(t_ast_lst));
	new->ast = ast;
	return (new);
}

void	init_parser(t_parser *parser)
{
	ft_bzero(parser, sizeof(parser));
	parser->state = 0;
	parser->ast_stack = NULL;
	parser->state_stack = state_lst_new(0);;
}

int		parse(t_parser *parser, t_ast **ast, t_list *token_list)
{
	t_list		*tmp = NULL;
	int			action;
	t_token		*dollar_token;

	dollar_token = ft_memalloc(sizeof(*dollar_token) * 1);
	dollar_token->value = ft_strdup("End token");
	dollar_token->state_info = NULL;
	dollar_token->delim = 0;
	dollar_token->id = $;
	ft_simple_lst_pushback(&token_list, ft_simple_lst_create(dollar_token));
	tmp = token_list;
	while (tmp)
	{
		action = get_action(tmp->data, parser->state);
		if (action == -1)
			return (check_reopen(parser->ast_stack, tmp));
		if (action == 10000)
		{
			if (parser->ast_stack->next)
				printf("error\n");
			*ast = parser->ast_stack->ast;
			return (PARSER_SUCCESS);
		}
		if (action >= FIRST_REDUCE_RULE)
		{
			/*
**					if (tmp->data)
**						printf(MAG"#"CYN"%s, %d"MAG"#\n"RESET , ((t_token *)tmp->data)->value, ((t_token *)tmp->data)->id);
*/
			reduce(&parser->state_stack, &parser->ast_stack, action - FIRST_REDUCE_RULE);
			parser->state = get_goto(parser->state_stack, action - FIRST_REDUCE_RULE);
			if (parser->state == -1)
				return (PARSER_ERROR);
		}
		else
		{
		//	printf("s%d\n", action);
			ft_genlst_add(&parser->ast_stack, ft_simple_lst_create(new_ast(tmp->data, -1)));
			tmp = tmp->next;
			parser->state = action;
		}
		ft_genlst_add(&parser->state_stack, new_state_lst(parser->state));
		//debug_pstate(parser->state_stack);
	}
	return (0);
}
