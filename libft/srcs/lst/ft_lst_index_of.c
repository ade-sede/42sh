#include "list.h"

int ft_genlst_index_of(void *lst, void *cur)
{
	t_gen_lst	*lst_cast = lst;
	int 	i = 0;
	while (lst_cast)
	{
		if (lst_cast == cur)
			return (i);
		lst_cast = lst_cast->next;
		i++;
	}
	return (-1);
}
