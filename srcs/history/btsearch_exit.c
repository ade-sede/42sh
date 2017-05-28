#include "line_editing.h"
#include "history.h"

int		btsearch_exit(t_line *line, t_hist *h)
{
	if (h->btsearch_list)
	{
		ft_double_lst_remove(&h->btsearch_list, NULL);
		h->btsearch_cur = NULL;
		ft_strclr(h->btsearch_buff);
		h->btsearch_buff_len = 0;
	}
	(void)line;
	return (1);
}
