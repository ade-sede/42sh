#include "history.h"
#include "libft.h"
#include "line_editing.h"
#include "shopt.h"

/*
**	OZSHHIST
*/

static t_list_d	*get_next(t_history *history)
{
	t_hist_node		*histnode = NULL;
	t_list_d		*target;
	size_t			len;

	if (singleton_env()->option & OZSHHIST)
	{
		len = ft_strlen(history->target);
		if (len == 0)
			return (NULL);
		if (history->current == history->command_list->last)
			target = history->new_command;
		else
			target = history->current->next;
		while (target)
		{
			if (ft_strnequ(history->target, histnode->hist_modif.line.str, len))
				break ;
			if (target == history->command_list->last)
				target = history->new_command;
			else
				target = target->next;
		}
	}
	else
	{
		if (history->current == history->command_list->last)
			target = history->new_command;
		else
			target = history->current->next;
	}
	return (target);
}
static t_list_d	*get_prev(t_history *history)
{
	t_hist_node		*histnode = NULL;
	t_list_d		*target;
	size_t			len;

	if (singleton_env()->option & OZSHHIST)
	{
		len = ft_strlen(history->target);
		if (len == 0)
			return (NULL);
		if (history->current == history->new_command)
			target = history->command_list->last;
		else
			target = history->current->prev;
		while (target)
		{
			histnode = target->data;
			if (ft_strnequ(history->target, histnode->hist_modif.line.str, len))
				break ;
			target = target->prev;
		}
	}
	else
	{
		if (history->current == history->new_command)
			target = history->command_list->last;
		else
			target = history->current->prev;
	}
	return (target);
}

int		history_next(t_line *line, t_history *history)
{
	t_list_d	*tmp;
	t_hist_node *histnode;

	if (!history->command_list || !history->command_list->first)
		return (0);
	tmp = get_next(history);
	if (tmp)
	{
		history->current = tmp;
		histnode = history->current->data;
		/* Refresh line */
		history_refresh_line(line, get_cmd_node(histnode)->line.str);
		/* line->pos = histnode->hist_modif.index; */
	}
	else
		put_termcap("bl");
	return (1);
}

int		history_prev(t_line *line, t_history *history)
{
	t_list_d	*tmp;
	t_hist_node *histnode;

	if (!history->command_list || !history->command_list->first)
		return (0);
	tmp = get_prev(history);
	if (tmp)
	{
		history->current = tmp;
		histnode = history->current->data;
		history_refresh_line(line, get_cmd_node(histnode)->line.str);
		/* line->pos = histnode->hist_modif.index; */
	}
	else
	{
		line->pos = ft_strlen(history->target);
		edit_refresh(line);
		put_termcap("bl");
	}
	return (1);
}
