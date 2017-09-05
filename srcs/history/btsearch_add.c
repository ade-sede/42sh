#ifndef NO_TERMCAPS
#include "line_editing.h"
#include "history.h"
#include <stdio.h>

void	create_strstr_btsearch_buff(t_list_d *item)
{
	t_hist		*h;
	t_list_d	*list;

	h = singleton_hist();
	if (ft_strstr(item->data, h->btsearch_buff))
	{
		list = ft_double_lst_create(item->data);
		if (h->btsearch_list == NULL)
			h->btsearch_list = ft_create_head(list);
		else
			ft_double_lst_add(&(h->btsearch_list), list);
	}
}

void	btsearch_search(t_hist *h)
{
	t_list_d	*list;
	t_list_d	*list_next;

	list = h->btsearch_list->first;
	while (list)
	{
		list_next = list->next;
		if (!(ft_strstr(list->data, h->btsearch_buff)))
			ft_double_lst_del_one(&h->btsearch_list, list, NULL);
		list = list_next;
	}
}

void	btsearch_first_search(t_hist *h)
{
	ft_double_lst_foreach(h->list->first, NULL, create_strstr_btsearch_buff, 1);
}

/*
**	void	debug(t_list_d *item)
**	{
**		printf("%s\n", (char*)item->data);
**	}
*/

void	btsearch_add(char keycode, t_line *line, t_hist *h)
{
	h->btsearch_buff[h->btsearch_buff_len] = keycode;
	h->btsearch_buff_len++;
	(h->btsearch_list == NULL) ? btsearch_first_search(h) : btsearch_search(h);
	if (h->btsearch_list && h->btsearch_list->first)
		btsearch_change_line(line, h, h->btsearch_list->first);
	else
		btsearch_change_line(line, h, NULL);
}
#endif
