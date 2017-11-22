#include "libft.h"
#include "t_history.h"
#include "shopt.h"

t_hist_node *create_hist_node(void)
{
	t_hist_node	*ret;

	ret = ft_memalloc(sizeof(*ret));
	w_newword(&ret->history.line);
	w_newword(&ret->hist_modif.line);
	ret->history.index = -1;
	ret->hist_modif.index = -1;
	return (ret);
}

void	destroy_hist_node(t_list_d *l)
{
	t_hist_node *node;
	if (l)
	{
		node = l->data;
		destroy_hist_cmd_node(&node->history);
		destroy_hist_cmd_node(&node->hist_modif);
		free(node);
	}
}

t_hist_cmd_node *get_cmd_node(t_hist_node *histnode)
{
	if (singleton_env()->option & HISTREEDIT)
		return (&histnode->history);
	else
		return (&histnode->hist_modif);
}


void	copy_cmd_node(t_hist_cmd_node *source, t_hist_cmd_node *dest)
{
	destroy_hist_cmd_node(dest);
	w_newword(&dest->line);
	w_addstr(&dest->line, source->line.str);
	dest->index = source->index;
	dest->timestamp = source->timestamp;
}

void	restore_cmd_node(t_list_d *ptr)
{
	t_hist_node *node;

	node = ptr->data;
	if (node)
	{
		if (node->history.modified || node->hist_modif.modified)
		{
			copy_cmd_node(&node->history, &node->hist_modif);
			node->history.modified = 0;
			node->hist_modif.modified = 0;
		}
	}
}
