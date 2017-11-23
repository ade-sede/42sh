#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "parser.h"

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
}

struct morpheme_lst	*lr_first(struct s_parser_lr *lr, struct morpheme_list *m_lst)
{
	struct morpheme_list *res = NULL;

	while (m_lst)
	{
		else if (IS_TOKEN(m_lst->m))
			add_unique_morpheme_lst(&res, m_lst->m);
		else if (IS_SYMBOL(m_lst->morpheme))
		{
			/*
			 **	m_lst s'ecrit Aß:
			 **	si A contient epsilon ou si c'est le premier symbol de la regle on ajoute
			 ** a firsts: soit le firsts deja trouver soit app recursif pour le trouver
			 **	sinon on break
			 */
			if (search_morpheme_lst(first_A, EPSILON) || m_lst == lr->grammar_rules[i].m_lst)
			{
				if (lr->firsts[m_lst->m])
					union_morpheme_lst(&lr->firsts[symb], lr->firsts[m_lst->m]);
			}
			else
				break;
		}
		m_lst = m_lst->next;
	}
}

static struct morpheme_lst	*init_firsts_symbol(struct s_parser_lr *lr, enum e_symbol symb)
{
	int	i;
	struct s_morpheme_lst	*child;
	
	i = get_first_grammar_rule(lr->grammar_rules, symb);
	while (i < NB_RULES && lr->grammar_rules[i].node == symb)
	{
		child = lr->grammar_rules[i].child;
		while (child)
		{
			else if (IS_TOKEN(child->m))
				add_unique_morpheme_lst(&lr->firsts[symb], child->m);
			else if (IS_SYMBOL(child->morpheme))
			{
				/*
				 **	child s'ecrit Aß:
				 **	si A contient epsilon ou si c'est le premier symbol de la regle on ajoute
				 ** a firsts: soit le firsts deja trouver soit app recursif pour le trouver
				 **	sinon on break
				 */
				if (search_morpheme_lst(first_A, EPSILON) || child == lr->grammar_rules[i].child)
				{
					if (lr->firsts[child->m])
						union_morpheme_lst(&lr->firsts[symb], lr->firsts[child->m]);
					else
						union_morpheme_lst(&lr->firsts[symb], init_firsts_symbol(lr, child->m));
				}
				else
					break;
			}
			child = child->next;
		}
		i++;
	}
	return (lr->firsts[symb]);
}

struct token_lst	*init_firsts(struct s_parser_lr *lr)
{
	int	i =0;

	while (i < NB_SYMBOLS)
	{
		if (lr->firsts[i] == NULL)
			frists[i] = init_firsts_symbol(lr, i)
		i++;
	}
}
