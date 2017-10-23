#include "parser_slr.h"
#include "parser.h"




#include <stdio.h>

void	debug_pstate(t_listint *stack)
{
	t_listint	*tmp;

	printf("state_stack: ");
	for (tmp = stack; tmp; tmp = tmp->next)
		printf("%d ", tmp->data);
	printf("\n");
}

int		parse(t_ast **ast, t_list *token_list)
{
	t_list		*tmp = NULL;
	t_listint	*state_stack = NULL;
	int			state;
	int			action;
	t_list		*ast_stack = NULL;

	state = 0;
	state_stack = ft_lstint_new(0);;
	tmp = token_list;
	while (tmp)
	{
		action = get_action(tmp->data, state);
		if (action == -1)
		{
			printf("Error action is -1\n");
			return (PARSER_ERROR);
		}
		if (action == 10000)
		{
			printf("APPARTIENT a la GRAMMAIRE\n");
			if (ast_stack->next)
				printf("error\n");
			*ast = ast_stack->data;
			return (PARSER_SUCCESS);
		}
		if (action >= 4242)
		{
			printf("r%d\n", action -4242);
			reduce(&state_stack, &ast_stack, action - 4242);
			state = get_goto(state_stack, action - 4242);
			if (state == -1)
				return (PARSER_ERROR);
		}
		else
		{
			printf("s%d\n", action);
			ft_simple_lst_add(&ast_stack, ft_simple_lst_create(new_ast(tmp->data, -1)));
			tmp = tmp->next;
			state = action;
		}
		ft_lstint_add(&state_stack, state);
		debug_pstate(state_stack);
	}
	return (0);
	/* return (NULL); */
}
