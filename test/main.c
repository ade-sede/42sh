#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "parser_lr.h"


/*
**	renvoie les symboles apres le point dans de la gramar_rule
*/

struct s_morpheme_lst *get_point(struct s_parser_lr *lr, int gramar_rule, int point)
{
	return (ft_genlst_get_n(lr->grammar_rules[gramar_rule].childs, point));
}

struct s_item *lr_closure(struct s_parser_lr *lr, struct s_item *kernel)
{
	struct s_item	*cur = NULL;
	struct s_item	*res = NULL;	//res pointe sur le debut de cur;
	enum e_token	a;
	int				added = 0;

	cur = dup_item_lst(kernel);
	res = cur;
	while (cur)
	{
		printf("curlst: "); debug_item_lst(lr, cur); printf("\n"); 
		a = cur->look_ahead;
		struct s_morpheme_lst *B = get_point(lr, cur->grammar_rule, cur->point);
		if (!B || !(IS_SYMBOL(B->m)))
		{
			cur = cur->next;
			continue ;
		}
		struct s_morpheme_lst *beta = dup_morpheme_lst(B->next);
		ft_genlst_pushback((void **)&beta, new_morpheme_lst(a));
		printf("beta a: ");debug_morpheme_lst(beta);printf("\n");
		struct s_morpheme_lst *firsts = lr_first(lr, beta);
		printf("firsts: "); debug_morpheme_lst(firsts); printf("\n");
		int		i = get_first_grammar_rule(lr->grammar_rules, B->m);
/*
**	each production B → γ in G ′ , and each terminal b ∈ FIRST ( βa) such that 
**	[ B → .γ,b ] 6∈ I do add [ B → .γ,b ] to I, here gama is represented by i
*/
		while (i < NB_RULES && lr->grammar_rules[i].node == B->m)
		{
			printf("gama: ");debug_grammar_rule(lr, i);printf("\n");
			struct s_morpheme_lst *tmp = firsts;
			while (tmp)
			{
				item_pushback_unique(&res, i, 0, tmp->m);
				printf("cur first: ");debug_morpheme_node(tmp);printf("\n");
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

/*
**	void	lr_goto(struct s_line **res, struct s_line *curr)
**	{
**		struct s_item *new_kernel = NULL;
**		struct s_line *new_new_line = NULL;
**	
**		new_line->kernel = new_kernel;
**		new_line->closure = closure(new_kernel);
**	}
*/

struct s_line *lr_items(struct s_parser_lr *lr)
{
	struct s_line	*res = NULL;
	struct s_line	*cur = NULL;
	struct s_item	*initial_kernel;

	initial_kernel = new_item(0, 0, DOLLAR);
	cur = new_line(0, initial_kernel, lr_closure(lr, initial_kernel));
	debug_line(lr, cur);
	res = cur;
	/*
	while (curr != NULL)
	{
		lr_goto(&res, curr);
		curr = curr->next;
	}
	*/
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
	lr_items(&lr);
	return 0;
}
