#include "libft.h"

/*
** Get the n'th node of the list from where we are. first is node 1
** first->next is node 2
*/

t_list_d	*ft_double_lst_get_n(t_list_d *first, int n)
{
	if (n == 0)
		return (NULL);
	if (n > 0)
	{
		while (first && n > 1)
		{
			n--;
			first = first->next;
		}
	}
	else if (n < 0)
	{
		while (first && n < -1)
		{
			n++;
			first = first->prev;
		}
	}
	if (!first)
		return (NULL);
	return (first);
}

t_list	*ft_simple_lst_get_n(t_list	*first, size_t n)
{
		if (n == 0)
				return (NULL);
		while (first && n > 1)
		{
				n--;
				first = first->next;
		}
		return (first);
}
