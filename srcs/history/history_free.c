#include "t_history.h"

void	free_history_node(t_list_d **node)
{
	if (*node)
	{
		destroy_hist_node(*node);
		free(*node);
	}
	*node = NULL;
}
