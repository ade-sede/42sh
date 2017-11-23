#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "parser_lr.h"


struct s_item *dup_item_lst->next(struct s_item *old)
{
	struct s_item *new;
	while (old->next)
	{
		ft_genlst->next_pushback(&new, new_item(old->next->gramar_rule, point, look_ahead));
		old = old->next;
	}
	return (new);
}

/*
**	renvoie les symboles apres le point dans de la gramar_rule
*/

struct s_item *get_point(struct s_parser *lr, int gramar_rule, int point)
{
	return (ft_genlst_get_i(lr->grammar_rules[gramar_rule].childs, point));
}

struct s_item *lr_closure(struct s_item *kernel)
{
	struct s_item *curr = NULL;
	struct s_item *res = NULL;
	enum e_symbol symbol_B;
	enum e_token a;
	int			added = 0;

	curr = dup_item_lst(kernel);
	while (curr)
	{
		a = current->look_ahead;
		struct s_item *B = get_point(lr, point);
		if (!B || !IS_SYMBOL(B->m))
		struct s_item *beta = B->next;
		int		i = get_first_grammar_rule(lr->gramar_rule, beta->m);
		while (i < NB_RULES && lr->grammar_rules[i].node == symbol_B)
		{
			ft_genlst_last(beta)->next = new_item(a);
			struct s_morpheme_lst *firsts = lr_first(lr, beta a);
			struct s_morpheme_lst *tmp = firsts;
			while (tmp)
			{
				pushback_unique(res, i, 0, tmp->m);
				tmp = tmp->next;
			}
			i++;
		}
		//free(beta);
		current = current->next;
	}
}
return (item_lst);
}

/*
**	goto prend une line avec un set d item, et pushback des lines sur line
*/

void	lr_goto(struct s_line **res, struct s_line *curr)
{
	struct s_item *new_kernel = NULL;
	struct s_line *new_new_line = NULL;

	new_line->kernel = new_kernel;
	new_line->closure = closure(new_kernel);
}

struct s_line	*lr_items(void)
{
	struct s_line *array = NULL;
	struct s_line *current_line;
	struct s_item *item_list_I = NULL;
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

struct s_line *(struct s_parser *lr)
{
	struct s_line *res;
	struct s_line *curr;
	add_item(curr, 0, 0, dollar);
	add_line(&res, curr);
	closure(curr);
	while (curr != NULL)
	{
		lr_goto(&res, curr);
		curr = curr->next;
	}
	return (res);
}

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
