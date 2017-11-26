#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "parser_lr.h"


struct s_item *dup_item_lst(struct s_item *old)
{
	struct s_item *new;
	struct s_item *new_tmp;

	new_tmp = new_item(old->grammar_rule, old->point, old->look_ahead);
	new = new_tmp;
	while (old->next)
	{
		new_tmp->next = new_item(old->next->grammar_rule, old->next->point, old->next->look_ahead);
		old = old->next;
		new_tmp = new_tmp->next;
	}
	return (new);
}

void	item_pushback_unique(struct s_item **item_lst, int grammar_rule, int point, enum e_token look_ahead)
{
	struct s_item *cur = *item_lst;

	if (!(cur))
		*item_lst = new_item(grammar_rule, point, look_ahead);
	while (cur)
	{
		if (cur->grammar_rule == grammar_rule && cur->point == point && cur->look_ahead == look_ahead)
			return ;
		if (!cur->next)
			cur->next = new_item(grammar_rule, point, look_ahead);
	}
}

/*
**	renvoie les symboles apres le point dans de la gramar_rule
*/

struct s_item *get_point(struct s_parser_lr *lr, int gramar_rule, int point)
{
	return (ft_genlst_get_n(lr->grammar_rules[gramar_rule].childs, point));
}

struct s_item *lr_closure(struct s_parser_lr *lr, struct s_item *kernel)
{
	struct s_item	*cur = NULL;
	struct s_item	*res = NULL;	//res pointe sur le debut de cur;
	enum e_symbol	symbol_B;
	enum e_token	a;
	int				added = 0;

	cur = dup_item_lst(kernel);
	res = cur;
	while (cur)
	{
		a = cur->look_ahead;
		struct s_item *B = get_point(lr, point);
		if (!B || !IS_SYMBOL(B->m))
		{
			cur = cur->next;
			continue ;
		}
		struct s_item *beta = dup_item_lst(B->next);
		ft_genlst_pushback(beta, new_item(a));
		int		i = get_first_grammar_rule(lr->gramar_rule, beta->m);
		struct s_morpheme_lst *firsts = lr_first(lr, beta);
/*
**	each production B → γ in G ′ , and each terminal b ∈ FIRST ( βa) such that 
**	[ B → .γ,b ] 6∈ I do add [ B → .γ,b ] to I, here gama is represented by i
*/
		while (i < NB_RULES && lr->grammar_rules[i].node == symbol_B)
		{
			struct s_morpheme_lst *tmp = firsts;
			while (tmp)
			{
				item_pushback_unique(&res, i, 0, tmp->m);
				tmp = tmp->next;
			}
			i++;
		}
		//free(beta);
		cur = cur->next;
	}
	return (res);
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

struct s_line *lr_items(struct s_parser *lr)
{
	struct s_line	*res = NULL;
	struct s_line	*cur = NULL;
	struct s_item	*initial_kernel;

	initial_kernel = new_item(0, 0, dollar);
	cur = new_line(0, initial_item, lr_closure(lr, initial_kernel));
	res = cur;
	/*
	while (curr != NULL)
	{
		lr_goto(&res, curr);
		curr = curr->next;
	}
	return (res);
	*/
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
