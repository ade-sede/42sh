#include "history.h"
#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include "env.h"

int	history_load(t_hist *h, t_env *env)
{
	int		fd;
	char		*line;
	char		*hist_file;
	t_list_d	*list;

	ft_bzero(h, sizeof(t_hist));
	hist_file = env_getenv((const char **)env->environ, "HISTFILE", NULL);
	if (!hist_file)
		hist_file = ".minishell_history";
	h->file = hist_file;
	h->list = NULL; 
	if ((fd = open(h->file, O_RDWR | O_CREAT)) == -1)
		return (0);
	chmod(h->file, S_IRUSR | S_IWUSR | S_IRGRP);
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
	close(fd);
	return (1);
}
