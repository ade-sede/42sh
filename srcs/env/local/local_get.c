#include "local.h"
#include "libft.h"

t_local_list	*local_get_node(t_local_list *first, const char *key)
{
	while (first)
	{
		if (ft_strequ(key, first->key))
			return (first);
		first = first->next;
	}
	return (NULL);
}

char			*local_get_value(t_local_list *first, const char *key)
{
	t_local_list	*node;

	node = local_get_node(first, key);
	if (!node)
		return (NULL);
	return (node->value);
}
