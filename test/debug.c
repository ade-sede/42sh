#include "parser_lr.h"
#include <stdio.h>

struct	s_sym_to_string
{
	int			symbol;
	char			*string;
};

struct s_sym_to_string	sts[] =
{
	{start_symbol,"s'"},
	{s,"s"},
	{c,"c"},
	{0, NULL},
};

void	debug_symbol(int m)
{
	int	i= 0;
	while (sts[i].string)
	{
		if (m == sts[i].symbol)
		{
			printf("%s", sts[i].string);
			return ;
		}
		i++;
	}
	/* debug_token(ast->token); */
	//printf("symbol not found\n");
}

static struct s_sym_to_string g_debug_token_id[] =
{
	{DOLLAR, "DOLLAR"  },
	{E, "E" },
	{F, "F" },
	{EPSILON, "EPSILON" },
	{-1, NULL}
};

void	debug_token(int m)
{
	int	i= 0;
	while (g_debug_token_id[i].string)
	{
		if (m == g_debug_token_id[i].symbol)
		{
			printf("%s", g_debug_token_id[i].string);
			return ;
		}
		i++;
	}
}

void		debug_grammar_rule(struct s_parser_lr *lr, int i) 
{
	struct s_morpheme_lst	*childs;
	childs = lr->grammar_rules[i].childs;
	debug_symbol(lr->grammar_rules[i].node);
	printf("-> ");
	if (!childs)
		printf("no_childs");
	while (childs)
	{
		if (IS_TOKEN(childs->m))
			debug_token(childs->m);
		else if (IS_SYMBOL(childs->m))
			debug_symbol(childs->m);
		else
		{
			printf("invalid symbol");
			break;
		}
//		printf("child i is : %d", childs->m);
		printf(" ");
		childs = childs->next;
	}
	printf("\n");
}
void	debug_gramar(struct s_parser_lr *lr)
{
	int	i = 0;
	
	while (i < NB_RULES)
	{
		debug_grammar_rule(lr, i);
		i++;
	}
}

void	debug_firsts(struct s_parser_lr *lr)
{
	int	i = FIRST_SYMBOL;

	while (i < NB_SYMBOLS + 1)
	{
		struct s_morpheme_lst	*childs;
		childs = lr->firsts[i];

		debug_symbol(i); printf(":");
		while (childs)
		{
			if (IS_TOKEN(childs->m))
				debug_token(childs->m);
			else if (IS_SYMBOL(childs->m))
				debug_symbol(childs->m);
			else
			{
				printf("invalid symbol");
				break;
			}
			//		printf("child i is : %d", childs->m);
			printf(" ");
			childs = childs->next;
		}
		i++;
		printf("\n");
	}
}
void	debug_morpheme_node(struct s_morpheme_lst *tmp)
{
		if (IS_TOKEN(tmp->m))
			debug_token(tmp->m);
		else if (IS_SYMBOL(tmp->m))
			debug_symbol(tmp->m);
		else
			printf("invalid symbol");
		printf(" ");
}

void	debug_morpheme_lst(struct s_morpheme_lst *tmp)
{
	while (tmp)
	{
		debug_morpheme_node(tmp);
		tmp = tmp->next;
	}
	printf("\n");
}

void	debug_item(struct s_parser_lr *lr, struct s_item *item)
{
	int		i = 0;

	printf("{[");
	struct s_morpheme_lst	*childs;
	childs = lr->grammar_rules[item->grammar_rule].childs;
	debug_symbol(lr->grammar_rules[item->grammar_rule].node);
	printf("-> ");
	if (!childs)
		printf("no_childs");
	while (childs)
	{
		if (i == item->point)
			printf(".");
		if (IS_TOKEN(childs->m))
			debug_token(childs->m);
		else if (IS_SYMBOL(childs->m))
			debug_symbol(childs->m);
		else
		{
			printf("invalid symbol");
			break;
		}
		//		printf("child i is : %d", childs->m);
		printf(" ");
		childs = childs->next;
		i++;
	}
	if (i == item->point)
		printf(".");
	printf(", ");
	debug_token(item->look_ahead);
	printf("]}; ");
}

void	debug_item_lst(struct s_parser_lr *lr, struct s_item *item)
{
	while (item)
	{
		debug_item(lr, item);
		item = item->next;
	}
}

void	debug_line(struct s_parser_lr *lr, struct s_line *l)
{
	printf("\nkernel:");
	debug_item_lst(lr, l->kernel);
	printf("\nclosure");
	debug_item_lst(lr, l->closure);
	printf("\n----------");
}

void	debug_closure_table(struct s_parser_lr *lr, struct s_line *l)
{
	printf("---------debug_closure_table----------");
	while (l)
	{
		debug_line(lr, l);
		l = l->next;
	}
}

void	debug_action_table(struct s_parser_lr *lr, struct s_line *l)
{
	printf("---------debug_action_table----------\n");
	while (l)
	{
		int	i = 0;
		while (i < NB_TOKEN)
		{
			if (l->action_table[i] >= 4242)
				printf("r%d ", l->action_table[i] - 4242);
			else if (l->action_table[i] == -1)
				printf("%d ", -1);
			else 
				printf("s%d ", l->action_table[i]);
			i++;
		}
		printf("\n");
		l = l->next;
	}
}

void	debug_goto_table(struct s_parser_lr *lr, struct s_line *l)
{
	printf("---------debug_goto_table----------\n");
	while (l)
	{
		int	i = 0;
		while (i < NB_SYMBOLS)
		{
			printf("%d ", l->goto_table[i]);
			i++;
		}
		printf("\n");
		l = l->next;
	}
}
