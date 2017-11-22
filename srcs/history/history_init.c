#include "history.h"
#include "libft.h"

int		history_init(t_history *hist)
{
	t_hist_node	*histnode_new;

	ft_double_lst_foreach(hist->command_list->first, NULL, restore_cmd_node, 1);
	histnode_new = create_hist_node();
	hist->new_command = ft_double_lst_create(histnode_new);
	hist->current = hist->new_command;
	return (1);
}
