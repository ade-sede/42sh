#include "btree.h"


void	aux(t_btree *root)
{
	aux(root->left);
	printer(node->data);
	aux(root->right);
}

void	btree_print(t_btree *root)
{
	if (!root)
		return ;
	aux(root);
}
