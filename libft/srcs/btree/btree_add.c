#include "btree.h"

t_btree	*btree_join(t_btree **root, t_btree	*new)
{
	new->left = *root;
	*root = new;
	return (*root);
}

t_btree	*btree_join_new(t_btree **root, void *data)
{
	t_btree	*new;

	new = btree_new(data);
	if (!new)
		return (NULL);
	return (btree_join(root, new));
}
