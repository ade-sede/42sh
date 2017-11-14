#include "libft.h"
#include "local.h"

int		local_remove(t_list **local_list, const char *key)
{
	t_list *node;

	node = local_get_node(*local_list, key);
	if (node)
		ft_simple_lst_del_one(local_list, node, free_local);
	return (1);
}
