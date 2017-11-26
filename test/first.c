#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "parser_lr.h"

int	search_morpheme_lst(struct s_morpheme_lst *a, t_morpheme m)
{
	while (a)
	{
		if (a->m == m)
			return (1);
		a = a->next;
	}
	return (0);
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
	
	i = get_first_grammar_rule(lr->grammar_rules, symb);
	while (i < NB_RULES && lr->grammar_rules[i].node == symb)
	{
		childs = lr->grammar_rules[i].childs;
		while (childs)
		{
			if (IS_TOKEN(childs->m))
				add_unique_morpheme_lst(&lr->firsts[symb], childs->m);
			else if (IS_SYMBOL(childs->m))
			{
				/*
				 **	childs s'ecrit Aß:
				 **	si A contient epsilon ou si c'est le premier symbol de la regle on ajoute
				 ** a firsts: soit le firsts deja trouver soit app recursif pour le trouver
				 **	sinon on break
				 */
				if (search_morpheme_lst(lr->firsts[symb], EPSILON) || childs == lr->grammar_rules[i].childs)
				{
					if (lr->firsts[childs->m])
						union_morpheme_lst(&lr->firsts[symb], lr->firsts[childs->m]);
					else
						union_morpheme_lst(&lr->firsts[symb], init_firsts_symbol(lr, childs->m));
				}
				else
					break;
			}
			childs = childs->next;
		}
		i++;
	}
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
}

struct s_morpheme_lst	*lr_first(struct s_parser_lr *lr, struct s_morpheme_lst *first)
{
	struct s_morpheme_lst	*res = NULL;
	struct s_morpheme_lst	*tmp = first;

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
				return (res);
		}
		else if (IS_SYMBOL(tmp->m))
		{
			if (lr->firsts[tmp->m])
				union_morpheme_lst(&res, lr->firsts[tmp->m]);
			else 
				printf("WARNING symbol possede no first\n");
			if (!(search_morpheme_lst(lr->firsts[tmp->m], EPSILON)))
				return (res);
		}
		tmp = tmp->next;
	}
	return (res);
}
