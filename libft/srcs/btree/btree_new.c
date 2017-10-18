#include "btree.h"

t_btree	*btree_new(void *data)
{
	t_btree	*new;

	if (!(new = ft_memalloc(sizeof(btree))))
		return (NULL);
	new->data = data;
}
