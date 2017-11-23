#include "parser_lr.h"
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

static struct s_static_grammar_rule rules[NB_RULES] = {
	{start_symbol, {s}},
	{s, {c, c}},
	{c, {E, c}},
	{c, {F}}
};

void	init_grammar_rules(struct s_parser_lr *lr)
{
	int	i = 0;

	while (i < NB_RULES)
	{
		lr->grammar_rules[i].node = rules[i].node;
		int	j = 0;
		lr->grammar_rules[i].childs = NULL;
		while (j < 7 && rules[i].childs[j] > 0)
		{
			ft_genlst_pushback(&lr->grammar_rules[i].childs, new_morpheme_lst(rules[i].childs[j]));
			j++;
		}
		i++;
	}
}

int		get_first_grammar_rule(struct s_grammar_rule *grammar_rule, enum e_symbol symbol) 
{
	int		i;

	i = 0;
	while (i < NB_RULES)
	{
		if (grammar_rule[i].node == symbol)
			return (i);
		i++;
	}
	return (-1);
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

