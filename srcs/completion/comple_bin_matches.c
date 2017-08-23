#include "env.h"
#include "completion.h"

void	comple_bin_matches_tripping(t_ternary_tree *node, char **matches)
{
	if (*cur < node->c && (!node->left || (node->left && *cur > node->left->c)))// aret
		return ternary_tree_insert_left(node, cur, str);
	else if (*cur > node->c && (!node->right || (node->right && *cur < node->right->c))) // aret
		return ternary_tree_insert_right(node, cur, str);
	else if (*cur < node->c)
		return ternary_tree_add(node->left, cur, str);
	else if (*cur > node->c)
		return ternary_tree_add(node->right, cur, str);
	else if (*cur == node->c && node->down)
		return ternary_tree_add(node->down, cur + 1, str);
	else if (*cur == node->c && node->down)
		return ternary_tree_insert_down(node, cur, str);
}

char	**comple_bin_matches(t_line *line, t_comple *c, char *current_word)
{
	t_ternary_tree *node;
	char		**matches;
	
	c->to_replace = get_start_word_cursor(line);
	matches = ft_memalloc(sizeof(char *) * 1000); ///////////////////////////////////////////////////
	comple_bin_matches_tripping(singleton_env()->tree, matches);
}
