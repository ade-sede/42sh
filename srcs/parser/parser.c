/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:38 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:40 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "libft.h"
#include "color.h"
#include <stdio.h>
#include "exec.h"

/*
**	void			debug_pstate(t_listint *stack)
**	{
**		t_listint	*tmp;
**
**		tmp = stack;
**		while (tmp)
**		{
**			tmp = tmp->next;
**		}
**		ft_putchar('\n');
**	}
**
**	void			debug_ast_stack(t_list *ast_stack)
**	{
**		t_list	*tmp;
**
**		tmp = ast_stack;
**		while (tmp)
**		{
**			debug_symbol(tmp->data);
**			tmp = tmp->next;
**		}
**		ft_putchar('\n');
**	}
**
*/

static int		check_reopen(t_ast_lst *ast_stack, t_list *token)
{
	int		reopen;

	(void)ast_stack;
	if ((reopen = ((t_token*)token->data)->id) == 666 || reopen == 42)
		return (PARSER_REOPEN);
	ft_dprintf(2, "42sh: parse error near `%s'\n", ((t_token*)token->data)->value);
	return (PARSER_ERROR);
}

static t_token	*init_dollar(void)
{
	t_token		*dollar_token;

	dollar_token = ft_memalloc(sizeof(*dollar_token) * 1);
	dollar_token->value = ft_strdup("End token");
	dollar_token->state_info = NULL;
	dollar_token->delim = 0;
	dollar_token->id = DOLAR;
	return (dollar_token);
}

static int		action_return(t_parser *parser, t_list *tmp,
		t_ast **ast, int act)
{
	if (act == -1)
		return (check_reopen(parser->ast_stack, tmp));
	if (parser->ast_stack->next)
		ft_dprintf(2, "error\n");
	*ast = parser->ast_stack->ast;
	return (PARSER_SUCCESS);
}

static void		parse_cut(t_parser *parser, t_list **tmp, int action)
{
	ft_genlst_add(&parser->ast_stack,
			ft_simple_lst_create(new_ast((*tmp)->data, 0)));
	*tmp = (*tmp)->next;
	parser->state = action;
}

int				parse(t_parser *parser, t_ast **ast, t_list *token_list)
{
	t_list		*tmp;
	int			action;

	ft_simple_lst_pushback(&token_list, ft_simple_lst_create(init_dollar()));
	tmp = token_list;
	while (tmp)
	{
		action = get_action(tmp->data, parser->state);
		if (action == -1 || action == 10000)
			return (action_return(parser, tmp, ast, action));
		if (action >= FIRST_REDUCE_RULE)
		{
			reduce(&parser->state_stack, &parser->ast_stack,
					action - FIRST_REDUCE_RULE);
			if ((parser->state = get_goto(parser->state_stack,
							action - FIRST_REDUCE_RULE)) == -1)
				return (PARSER_ERROR);
		}
		else
			parse_cut(parser, &tmp, action);
		ft_genlst_add(&parser->state_stack, new_state_lst(parser->state));
	}
	return (0);
}
