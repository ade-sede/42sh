#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "parser_lr.h"

struct s_line *new_line(int state, struct s_item *kernel, struct s_item *closure)
{
	struct s_line *new_line;
	if (!(new_line = (struct s_line *)calloc(sizeof(struct s_line), 1)))
		return NULL;
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
	if (!(item = (struct s_item *)calloc(sizeof(struct s_item), 1)))
		return NULL;
	item->grammar_rule = grammar_rule;
	item->point = point;
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
	if (!(morpheme = (struct s_morpheme_lst *)calloc(sizeof(struct s_morpheme_lst), 1)))
		return NULL;
	morpheme->m = m;
	return morpheme;
}
