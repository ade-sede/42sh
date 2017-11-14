#include "history.h"
#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include "t_env.h"
#include "environ.h"

static void	init_hist_struct(t_hist *h)
{
	ft_bzero(h, sizeof(t_hist));
	h->list = NULL;
	h->last_read = NULL;
	h->writen_buff = ft_strnew(4096);
	h->btsearch_buff = ft_strnew(4096);
}

t_cmd_node *ft_node_new(char *cat, int index)
{
	t_cmd_node *ret;

	ret = ft_memalloc(sizeof(t_cmd_node));
	ret->index = index;
	gettimeofday(&ret->timestamp, NULL);
	ret->line = ft_strdup(cat);
	return (ret);
}

void	routine(t_hist *h, char *cat, int index)
{
	t_list_d	*list;

	list = ft_double_lst_create(ft_node_new(cat, index));
	if (h->list == NULL)
		h->list = ft_create_head(list);
	else
		ft_double_lst_add(&h->list, list);
}

int			history_load(t_hist *h)
{
	int			fd;
	char		*line;
	char		*cat;

	cat = NULL;
	init_hist_struct(h);
	if ((fd = open(histfile(), O_RDWR | O_CREAT, 0644)) == -1)
		return (0);
	while (get_next_line(fd, &line))
	{
		if (cat)
		{
			cat[ft_strlen(cat) - 1] = '\n';
			cat = ft_strjoin_free(cat, line, 0b11);
		}
		if (!cat)
			cat = line;
		if (charcmp(cat, ft_strlen(cat) - 1, '\\'))
			continue ;
		routine(h, cat, -1);
		cat = NULL;
	}
	close(fd);
	h->last_read = (h->list) ? h->list->last : NULL;
	return (1);
}
