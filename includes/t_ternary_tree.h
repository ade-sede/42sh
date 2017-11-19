#ifndef T_TERNARY_TREE_H
# define T_TERNARY_TREE_H

typedef struct				s_ternary_tree
{
	char					c;
	char					*match;
	struct s_ternary_tree	*left;
	struct s_ternary_tree	*right;
	struct s_ternary_tree	*down;
}							t_ternary_tree;

void						free_ternary_tree(t_ternary_tree *node);
void						test_ternary_tree();
void						ternary_tree_add(t_ternary_tree *node,
		char *cur, char *str);
t_ternary_tree				*ternary_tree_new_down(char *str, char *cur);
t_ternary_tree				*ternary_tree_new(char c);
void						ternary_tree_print(t_ternary_tree *node);
#endif
