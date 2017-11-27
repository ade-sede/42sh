#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "parser_lr.h"

struct s_item *dup_item_lst(struct s_item *old)
{
	struct s_item *new;
	struct s_item *new_tmp;

	if (!old)
		return (NULL);
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

struct s_morpheme_lst *dup_morpheme_lst(struct s_morpheme_lst *old)
{
	struct s_morpheme_lst *new;
	struct s_morpheme_lst *new_tmp;

	if (!old)
		return (NULL);
	new_tmp = new_morpheme_lst(old->m);
	new = new_tmp;
	while (old->next)
	{
		new_tmp->next = new_morpheme_lst(old->next->m);
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
		cur = cur->next;
	}
}

struct s_line *new_line(int state, struct s_item *kernel, struct s_item *closure)
{
	struct s_line *new_line;
	if (!(new_line = (struct s_line *)ft_memalloc(sizeof(struct s_line))))
		return NULL;
	new_line->next = NULL;
	new_line->state = state;
	new_line->kernel = kernel;
	new_line->closure = closure;
	ft_memset(new_line->goto_table, -1, NB_SYMBOLS);
	ft_memset(new_line->action_table, -1, NB_TOKEN);
	return new_line;
}

/*
**	struct s_line *add_line(struct s_line **array, int state, struct s_item *item_lst) {
**		struct s_line *new_line = create_line(state);
**		if (!new_line) {
**			printf("BAD ALLOCATION\n");
**			exit(EXIT_FAILURE);
**		}
**		new_line->state = state;
**		new_line->item_list = item_list;
**		return (ft_genlst_add((void **)array, new_line));
**	}
*/

struct s_item *new_item(int grammar_rule, int point, enum e_token token)
{
	struct s_item *item;
	if (!(item = (struct s_item *)ft_memalloc(sizeof(struct s_item))))
		return NULL;
	item->grammar_rule = grammar_rule;
	item->point = point;
	item->next = NULL;
	item->look_ahead = token;
	return item;
}

/*
**	struct s_item *add_item(struct s_item **item_lst, struct s_grammar_rule *rule, int point, enum morpheme token) {
**		struct s_item *new_item = create_item(rule, point, token);
**		if (!new_item) {
**			printf("BAD ALLOCATION\n");
**			exit(EXIT_FAILURE);
**		}
**		return (ft_genlst_add((void **)item_lst, new_item));
**	}
*/

struct s_morpheme_lst *new_morpheme_lst(t_morpheme m) {
	struct s_morpheme_lst *morpheme;
	if (!(morpheme = (struct s_morpheme_lst *)ft_memalloc(sizeof(struct s_morpheme_lst))))
		return NULL;
	morpheme->next = NULL;
	morpheme->m = m;
	return morpheme;
}
