#include "t_history.h"
#include "failure.h"
#include "environ.h"
#include "libft.h"
#include <sys/time.h>
#include "get_next_line.h"

void			set_hist_cmd_node(char *line, int index, int modif, t_hist_cmd_node *nd)
{
	nd->index = index;
	free(nd->line);
	if (line)
		nd->line = ft_strdup(line);
	else
		nd->line = NULL;
	nd->modified = modif;
	gettimeofday(&nd->timestamp, NULL);
}

t_hist_node		*new_node(void)
{
	t_hist_node *ret;

	ret = ft_memalloc(sizeof(t_hist_node));
	set_hist_cmd_node(NULL, 0, 0, &ret->history);
	set_hist_cmd_node(NULL, 0, 0, &ret->hist_modif);
	return (ret);
}

void			reset_cmd_node(t_history *hist)
{
	t_list_d	*start;
	t_hist_node *nd;

	start = hist->command_list->first;
	while (start)
	{
		if ((nd = start->data)->hist_modif.modified)
		{
			set_hist_cmd_node(nd->history.line, nd->history.index, 0,
					&nd->hist_modif);
		}
		start = start->prev;
	}
}

/*fonction appeler, modifie current*/
void			set_hist_node(t_history *hist, char *line, int index)
{
	t_hist_node *nd;

	nd = hist->current_node->data;
	set_hist_cmd_node(line, index, 1, &nd->hist_modif);
}

/*fonction appeler, met a jour le nouveau noeud*/
void			set_new_hist_cmd(t_history *hist, char *str)
{
	t_hist_node *nd;

	if (str)
		set_hist_cmd_node(str, ft_strlen(str), 0,
				&((t_hist_node *)hist->command_list->last->data)->history);
	else
	{
		if ((nd = hist->current_node->data))
			set_hist_cmd_node(nd->hist_modif.line, nd->hist_modif.index, 0,
				&((t_hist_node *)hist->command_list->last->data)->history);
		reset_cmd_node(hist);
	}
	push_in_hist_list_null(hist);
}
