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

static struct s_firsts_of_symbol	init_firsts_symbol(struct s_parser_lr *lr, enum e_symbol symb)
{
	int	i;
	struct s_morpheme_lst	*childs;
	
	i = get_first_grammar_rule(lr->grammar_rules, symb);
	lr->firsts[symb].nullable = 0;
    printf("symbol ");
    debug_symbol(symb);
    printf("\n");
	while (i < NB_RULES && lr->grammar_rules[i].node == symb)
	{
        //debug_firsts(lr);
		childs = lr->grammar_rules[i].childs;
		if (!childs)
			lr->firsts[symb].nullable = 1;
		while (childs)
		{
			if (IS_TOKEN(childs->m))
			{
				add_unique_morpheme_lst(&lr->firsts[symb].lst, childs->m);
				break;
			}
			else if (IS_SYMBOL(childs->m))
			{
				/*
				 **	childs s'ecrit Aß:
				 **	si A contient epsilon ou si c'est le premier symbol de la regle on ajoute
				 ** a firsts: soit le firsts deja trouver soit app recursif pour le trouver
				 **	sinon on break
				 */
				//if (lr->firsts[symb].nullable || childs == lr->grammar_rules[i].childs)
					//TODO: /* if faudrait regarder la suite si si c'est nullable */
					if (childs->m == symb && !lr->firsts[symb].nullable)
                    	break ;
					else if (childs->m == symb && lr->firsts[symb].nullable)
					{
						childs = childs->next;
						continue ;
					}
					struct s_firsts_of_symbol	beta;
                    if (lr->firsts[childs->m].lst)
						beta = lr->firsts[childs->m];
					else 
						beta = init_firsts_symbol(lr, childs->m);
					union_morpheme_lst(&lr->firsts[symb].lst, beta.lst);
					/* leaks */
					/* si on est arrive au bout et que le symbole est nullable */
					if (!(childs->next) && beta.nullable)
						lr->firsts[symb].nullable = 1;
					/* sinon on va a la regle suivante */
					if (!beta.nullable)
						break ;
			}
			childs = childs->next;
		}
		i++;
	}
	return (lr->firsts[symb]);
}

void	init_firsts(struct s_parser_lr *lr)
{
	int	i = 0;

	while (i < NB_SYMBOLS)
	{
		if (lr->firsts[i].lst == NULL)
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
	 **	on ajoute firsts (A) dans res tant que A est nullable
	 */

	while (tmp)
	{
		if (IS_TOKEN(tmp->m))
		{
			add_unique_morpheme_lst(&res, tmp->m);
			return (res);
		}
		else if (IS_SYMBOL(tmp->m))
		{
			if (lr->firsts[tmp->m].lst)
				union_morpheme_lst(&res, lr->firsts[tmp->m].lst);
			if (!(lr->firsts[tmp->m].nullable))
				return (res);
		}
		tmp = tmp->next;
	}
	return (res);
