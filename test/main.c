#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "parser_lr.h"

/*
struct item *lr_closure(struct item **item_lst)
{
	struct item *current;
	enum morpheme symbol_B;
	enum morpheme token_a;
	int			added;

	while (added)
	{
		current = item_lst;
		while (current)
		{
			current = item_lst;
			token_a = current->token;
			if (!symbol_B = current->rule[point] == 0)
				;
			char *beta = current->rule[point + 1];
			int		i = find_first_rule(symbol_B);
			while (i < NB_RULES && rules[i].node == symbol_B)
			{
				for b in first(beta, token_a)
				add_item(item_lst, &rules[i], 0, b);
				i++;
			}
			current = current->next;
		}
	}
	return (item_lst);
}

struct item *lr_goto(struct item *item_lst, enum morpheme symbol)
{

}

struct line	*lr_items(void)
{
	struct line *array = NULL;
	struct line *current_line;
	struct item *item_list_I = NULL;
	add_item(&item_list_I, &rules[0], 0, dollar);
	closure(&item_list_I);
	current_line = add_line(&array, 0, item_list_I);

	while (added)
	{ 
		while (current_line)
		{
			enum morpheme X;
			while (X < NB_MORPHENE)
			{
				item_list_I = lr_goto(current_line->item_lst, X);
				if (item_list_I != NULL && !search_items_in_array(item_list_I))
					add_line(&array, 0, item_list_I);
			}
			current_line = current_line->next;
		}
	}
}
*/

int main(void)
{
	struct	s_parser_lr lr;
	int		i;

	ft_bzero(&lr, sizeof(struct s_parser_lr));
	init_grammar_rules(&lr);
	debug_gramar(&lr);
	i = get_first_grammar_rule(lr.grammar_rules, start_symbol);
	debug_grammar_rule(&lr, i);
	init_firsts(&lr);
	debug_firsts(&lr);
	return 0;
}
