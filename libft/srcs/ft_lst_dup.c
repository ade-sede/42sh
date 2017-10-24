#include "libft.h"
#include "list.h"

/*
**	Creates a copy of the original list. Each node is a new one, with a fresh
**	address, but the original list and the copy both have the same data.
**	It must never be freed in both list.
*/

void	ft_simple_lst_dup(t_list **new_list_first, t_list *original)
{
	t_list	*new_node;

	new_node = NULL;
	if (!new_list_first)
		return ;
	while (original)
	{
		new_node = ft_simple_lst_create(original->data);
		ft_simple_lst_pushback(new_list_first, new_node);
		original = original->next;
	}
}
