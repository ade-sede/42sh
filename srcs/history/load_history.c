#include "history.h"
#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>

int	history_load(t_hist *h)
{
	int		fd;
	char		*line;
	t_list_d	*list;

	ft_bzero(h, sizeof(t_hist));
	h->list = NULL; 
	if ((fd = open("minishell_history", O_RDWR | O_CREAT)) == -1)
		return (0);
	chmod("minishell_history", S_IRUSR | S_IWUSR | S_IRGRP);
	while (get_next_line(fd, &line))
	{
		list = ft_double_lst_create(line);
		if (h->list == NULL)
			h->list = ft_create_head(list);
		else
			ft_double_lst_add(&h->list, list); 
	}
	h->writen_buff = ft_strnew(4096);
	h->btsearch_buff = ft_strnew(4096);
	return (1);
}
