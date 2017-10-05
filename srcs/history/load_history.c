#include "history.h"
#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include "env.h"

static void	init_hist_struct(t_hist *h, t_env *env)
{
	char		*hist_file;

	ft_bzero(h, sizeof(t_hist));
	hist_file = env_getenv((const char **)env->environ, "HISTFILE", NULL);
	if (!hist_file)
		hist_file = ".minishell_history";
	h->file = hist_file;
	h->list = NULL;
	h->writen_buff = ft_strnew(4096);
	h->btsearch_buff = ft_strnew(4096);
}

int			history_load(t_hist *h, t_env *env)
{
	int			fd;
	char		*line;
	char		*cat;
	t_list_d	*list;
	size_t		len;

	cat = NULL;
	init_hist_struct(h, env);
	if ((fd = open(h->file, O_RDWR | O_CREAT, 0644)) == -1)
		return (0);
	/* h->fd = fd; */
	while (get_next_line(fd, &line))
	{
		len = ft_strlen(line);
		if (cat)
		{
			cat[ft_strlen(cat) - 1] = '\n';
			cat = ft_strjoin_free(cat, line, 0b11);
		}
		if (!cat)
			cat = line;
		if (charcmp(line, len - 1, '\\'))
			continue ;
		list = ft_double_lst_create(cat);
		cat = NULL;
		if (h->list == NULL)
			h->list = ft_create_head(list);
		else
			ft_double_lst_add(&h->list, list);
	}
	close(fd);
	return (1);
}
