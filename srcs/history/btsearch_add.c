#include "line_editing.h"
#include "history.h"

void	delone_strstr_btsearch_buff(t_list_d *item)
{
	t_hist	*h;

	h = singleton_hist();
	if (!(ft_strstr(item->data, h->btsearch_buff)))
		ft_double_lst_del_one(&h->btsearch_list, item, ft_free);
}

void	create_strstr_btsearch_buff(t_list_d *item)
{
	t_hist	*h;
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
	ft_double_lst_foreach(h->btsearch_list->first, NULL, delone_strstr_btsearch_buff,1);
}

void	btsearch_first_search(t_hist *h)
{
	ft_double_lst_foreach(h->list->first, NULL, create_strstr_btsearch_buff, 1);
}

void	btsearch_add(char keycode, t_line *line, t_hist *h)
{
	h->btsearch_buff[h->btsearch_buff_len] = keycode;
	h->btsearch_buff_len++;
	printf("\n%s\n", h->btsearch_buff);
	(h->btsearch_list == NULL) ?  btsearch_first_search(h) : btsearch_search(h);
	if (h->btsearch_list && h->btsearch_list->first)
	{
		h->btsearch_cur = h->btsearch_list->first;
		ft_strclr(line->buff);
		ft_strcpy(line->buff, h->btsearch_cur->data);
	}
}
