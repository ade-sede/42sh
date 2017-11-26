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
	printf("kernel:");
	debug_item_lst(lr, l->kernel);
	printf("\nclosure");
	debug_item_lst(lr, l->closure);
}
