#include "libft.h"
#include "t_history.h"

int		history_push(t_lst_head **head, t_list_d *node)
{
	t_hist_node *n;

	n = node->data;
	update_timestamp(n->history);
	if (*head)
		ft_double_lst_pushback(head, node);
	else
		*head = ft_create_head(node);
	return (1);
}
