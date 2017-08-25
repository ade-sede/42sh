#include <stdio.h>
#include "completion.h"
/*
**	
**	parcours l arbre jusqu'a ce qu il nexiste plus de node qui match *cur, appelle alors une des fonction d insertion
**	
*/


/*
**	
**	insere le nouveau neud new_down a gauche de node comme dans un liste doublement chaine 
**	
*/

t_ternary_tree		*ternary_tree_new(char c)
{
	t_ternary_tree *new;

	if (!(new = ft_memalloc(sizeof(t_ternary_tree))))
		exit(1);
	new->c = c;
	return (new);
}

void			ternary_tree_print(t_ternary_tree *node)
{
	if (!node)
		return ;
	printf("c is %c\n", node->c);
	if (node->match)
		printf("match is %s\n", node->match);
	if (node->left)
		printf("\n left \n");
	ternary_tree_print(node->left);
	if (node->down)
		printf("\n down \n");
	ternary_tree_print(node->down);
	//put_termcap("do");
	if (node->right)
		printf("\n right\n");
	ternary_tree_print(node->right);
}

t_ternary_tree		*ternary_tree_new_down(char *str, char *cur)
{
	t_ternary_tree *res;
	t_ternary_tree *tmp;

	res = ternary_tree_new(*cur);
	tmp = res;
	cur++;
	while (*cur)
	{
		tmp->down = ternary_tree_new(*cur);
		if (*cur)
			tmp = tmp->down;
		cur++;
	}
	tmp->match = ft_strdup(str);
	return (res);
}


void	ternary_tree_insert_left(t_ternary_tree *node, char *cur, char *str)
{
	t_ternary_tree *new_down;
	t_ternary_tree *left;
	
	left = NULL;
	new_down = ternary_tree_new_down(str, cur);
	left = node->left;
	node->left = new_down;
	if (left)
		new_down->left = left;
}

void	ternary_tree_insert_right(t_ternary_tree *node, char *cur, char *str)
{
	t_ternary_tree *new_down;
	t_ternary_tree *right;
	
	right = NULL;
	new_down = ternary_tree_new_down(str, cur);
	right = node->right;
	node->right = new_down;
	if (right)
		new_down->right = right;
}

void	ternary_tree_insert_down(t_ternary_tree *node, char *cur, char *str)
{
	t_ternary_tree *new_down;

	if (!*cur) // cela signifie que str avait deja ete insere dans l arbre
		return ;
	new_down = ternary_tree_new_down(str, cur);
	node->down = new_down;
}


void	ternary_tree_add(t_ternary_tree *node, char *cur, char *str)
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
	else if (*cur == node->c && !node->down)
		return ternary_tree_insert_down(node, cur + 1, str);
}

void		test_ternary_tree()
{
	char	*str;
	t_ternary_tree *tree;

	str = "ab";
	tree = ternary_tree_new_down(str, str);
	ternary_tree_print(tree);
	str = "ba";
	printf("\n test 1\n");
	ternary_tree_add(tree, str, str);
	ternary_tree_print(tree);
}
