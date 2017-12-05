#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "parser_lr.h"

struct s_morpheme_lst *	search_morpheme_lst(struct s_morpheme_lst *a, t_morpheme m)
{
	while (a)
	{
		if (a->m == m)
			return (a);
		a = a->next;
	}
	return (NULL);
}

struct s_morpheme_lst *add_unique_morpheme_lst(struct s_morpheme_lst **a, t_morpheme m)
{
	struct s_morpheme_lst	*new;
	if (search_morpheme_lst(*a, m))
		return (*a);
	new = new_morpheme_lst(m);
	ft_genlst_add(a, new);
	return (*a);
}

/*
** malloc b elem that is put on a
*/

struct s_morpheme_lst *union_morpheme_lst(struct s_morpheme_lst **a, struct s_morpheme_lst *b)
{
	while (b)
	{
		add_unique_morpheme_lst(a, b->m);
		b = b->next;
	}
	return (*a);
}

static struct s_morpheme_lst	*init_firsts_symbol(struct s_parser_lr *lr, enum e_symbol symb)
{
	int	i;
	struct s_morpheme_lst	*childs;
	int	nullable = 0;
	
	i = get_first_grammar_rule(lr->grammar_rules, symb);
    printf("symbol ");
    debug_symbol(symb);
    printf("\n");
	while (i < NB_RULES && lr->grammar_rules[i].node == symb)
	{
        //debug_firsts(lr);
		childs = lr->grammar_rules[i].childs;
		if (!childs)
		while (childs)
		{
			if (IS_TOKEN(childs->m))
				add_unique_morpheme_lst(&lr->firsts[symb]->lst, childs->m);
			else if (IS_SYMBOL(childs->m))
			{
				/*
				 **	childs s'ecrit Aß:
				 **	si A contient epsilon ou si c'est le premier symbol de la regle on ajoute
				 ** a firsts: soit le firsts deja trouver soit app recursif pour le trouver
				 **	sinon on break
				 */
				if (lr->firsts[symb]->nullable || childs == lr->grammar_rules[i].childs)
				{
					if (childs->m == symb)
                        break ;
                    else if (lr->firsts[childs->m]->lst)
						union_morpheme_lst(&lr->firsts[symb]->lst, lr->firsts[childs->m]);
					else if (childs->m)
					{
						struct s_morpheme_lst	*beta = init_firsts_symbol(lr, childs->m);
						int no_epsilon = 0;
						if (!(search_morpheme_lst(beta, EPSILON)))
							no_epsilon = 1;
						/* leaks */
						union_morpheme_lst(&lr->firsts[symb], beta);
						if (no_epsilon)
							break ;
					}
				}
				else
					break;
			}
			childs = childs->next;
		}
		/* si on est arrive au bout et qu il ya epsilon le symbol est nullable */

		if (!(childs) && search_morpheme_lst(lr->firsts[symb], EPSILON))
			nullable = 1;
		i++;
	}
	/* si le symbol n 'est pas nullable il faut retirer epsilon 
	 * par ex : A -> EPSILON TK_LOL
	 * 			A -> TK_LOL
	 */
	struct s_morpheme_lst *epsilon_node = NULL;
	if (nullable == 0 && (epsilon_node = search_morpheme_lst(lr->firsts[symb], EPSILON)))
		ft_genlst_del_one(&lr->firsts[symb], epsilon_node, NULL);
	return (lr->firsts[symb]);
}

void	init_firsts(struct s_parser_lr *lr)
{
	int	i =0;

	while (i < NB_SYMBOLS)
	{
		if (lr->firsts[i] == NULL)
			lr->firsts[i] = init_firsts_symbol(lr, i);
		i++;
	}
	//debug_firsts(lr);
}

struct s_morpheme_lst	*lr_first(struct s_parser_lr *lr, struct s_morpheme_lst *first)
{
	struct s_morpheme_lst	*res = NULL;
	struct s_morpheme_lst	*tmp = first;
	struct s_morpheme_lst	*epsilon_node = NULL;

	/*
	 **	tmp s'ecrit Aß:
	 **	on ajoute firsts (A) dans res tant que A contient epsilon 
	 */

	while (tmp)
	{
		if (IS_TOKEN(tmp->m))
		{
			add_unique_morpheme_lst(&res, tmp->m);
			if (tmp->m != EPSILON)
			{
				/*supression de epsilon si token != epsilon */
				if ((epsilon_node = search_morpheme_lst(res, EPSILON)))
					ft_genlst_del_one(&res, epsilon_node, NULL);
				return (res);
			}
		}
		else if (IS_SYMBOL(tmp->m))
		{
			if (lr->firsts[tmp->m])
				union_morpheme_lst(&res, lr->firsts[tmp->m]);
			else 
				printf("WARNING symbol possede no first\n");
			if (!(search_morpheme_lst(lr->firsts[tmp->m], EPSILON)))
			{
				/*supression de epsilon si regle contient pas epsilon*/
				if ((epsilon_node = search_morpheme_lst(res, EPSILON)))
					ft_genlst_del_one(&res, epsilon_node, NULL);
				return (res);
			}
		}
		tmp = tmp->next;
	}
	return (res);
}
