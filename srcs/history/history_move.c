#include "history.h"

int		strnequ_writen_buff(void *data)
{
	int len;

	len = ft_strlen(singleton_hist()->writen_buff);
	if (len == 0)
		return (1);
	if (ft_strnequ(data, singleton_hist()->writen_buff, len))
	{
		printf("\n writen buff %s data %s len %d\n", singleton_hist()->writen_buff, data, len);
		return (1);
	}
	return (0);
}

int	history_next(t_line *line, t_hist *h)
{
	t_list_d	*tmp;

	tmp = NULL;
	tmp = ft_double_lst_return_if((h->cur) ? h->cur->next : h->list->first, strnequ_writen_buff, 1);
	printf("\n writen_buff %s h->cur %s tmp %s\n", singleton_hist()->writen_buff, (h->cur) ? h->cur->data : "null", (tmp) ? tmp->data : "null");
	if (tmp)
	{
		h->cur = tmp;
		edit_line_init(line);
		ft_strclr(line->buff);
		ft_strcpy(line->buff, (const char *)h->cur->data);
		line->len = ft_strlen((const char *)h->cur->data);
		line->pos = line->len;
	}
	else
		put_termcap("bl");
	return (1);
}

int	history_prev(t_line *line, t_hist *h)
{
	t_list_d	*tmp;

	tmp = NULL;
	tmp = ft_double_lst_return_if((h->cur) ? h->cur->prev : h->list->first, strnequ_writen_buff, -1);
	printf("\n writen_buff %s h->cur %s tmp %s\n", singleton_hist()->writen_buff, (h->cur) ? h->cur->data : "null", (tmp) ? tmp->data : "null");
	if (tmp)
	{
		h->cur = tmp;
		edit_line_init(line);
		ft_strclr(line->buff);
		ft_strcpy(line->buff, (const char *)h->cur->data);
		line->len = ft_strlen((const char *)h->cur->data);
		line->pos = line->len;
	}
	else
		put_termcap("bl");
	return (1);
}

int	history_move_init(t_line *line, t_hist *h)
{
	ft_strcpy(h->writen_buff, line->buff);
	printf("\n%s\n",h->writen_buff);
	return (1);
}

int	history_move_exit(t_line *line, t_hist *h)
{
	ft_strclr(h->writen_buff);
	(void)line;
	return (1);
}
