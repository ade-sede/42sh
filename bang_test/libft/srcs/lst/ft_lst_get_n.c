#include "libft.h"
#include "list.h"

/*
** 0 is current node, 1 is next, -1 is prev.
*/

t_list_d	*ft_double_lst_get_n(t_list_d *first, int n)
{
	if (n == 0)
		return (first);
	if (!first)
		return (NULL);
	if (n > 0)
	{
		while (first && n)
		{
			--n;
			first = first->next;
		}
	}
	if (n < 0)
	{
		while (first && n)
		{
			++n;
			first = first->prev;
		}
	}
	return (first);
}

/*
**	0 is the current node, 1 is node->next;
*/

t_list		*ft_simple_lst_get_n(t_list *first, size_t n)
{
	if (n == 0)
		return (first);
	while (first && n)
	{
		n--;
		first = first->next;
	}
	return (first);
}
