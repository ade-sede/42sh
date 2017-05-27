#include "history.h"

int	history_next(t_line *line)
{
	t_hist	*h;

	h = singleton_hist();
	if (h->cur == h->list->last)
		put_termcap("bl");
	else if (h->cur == NULL)
		h->cur = h->list->first;
	else if (h->cur->next != NULL)
		h->cur = h->cur->next;
	edit_line_init(line);
	ft_strcpy(line->buff, (const char *)h->cur->data);
	line->len = ft_strlen((const char *)h->cur->data);
	line->pos = line->len;
	return (1);
}

int	history_prev(t_line *line)
{
	t_hist	*h;

	h = singleton_hist();
	if (h->cur == NULL || h->cur == h->list->first)
		put_termcap("bl");
	else if (h->cur->prev != NULL)
	{
		h->cur = h->cur->prev;
		edit_line_init(line);
		ft_strcpy(line->buff, (const char *)h->cur->data);
		line->len = ft_strlen((const char *)h->cur->data);
		line->pos = line->len;
	}
	return (1);
}

int	history_move_init(t_line *line, t_hist *hist)
{
	hist->writen_buff = ft_strdup(line->buff);
}
