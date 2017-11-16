#include "history.h"
#include "failure.h"
#include "environ.h"

/*
 ** void	history_refresh_command(t_hist *h, char *command)
 ** {
 ** 	write(h->fd, command, ft_strlen(command));
 ** 	write(h->fd, "\n", 1);
 ** }
 **
 ** void	history_write_last_command(void)
 ** {
 ** 	t_hist		*h;
 ** 	t_list_d	*list;
 **
 ** 	h = singleton_hist();
 ** 	list = h->list->first;
 ** 	history_refresh_command(h, list->data);
 ** }
 */

char		*histfile(void)
{
	t_env	*env;
	char	*hist_file;

	env = singleton_env();
	hist_file = env_getenv((const char **)env->environ, "HISTFILE", NULL);
	return(hist_file);
}

static int		write_to_hist(char *value, int fd)
{
	size_t		i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '\n')
			write(fd, "\\", 1);
		write(fd, value + i, 1);
		++i;
	}
	return (1);
}

void			history_write_to_histfile(t_list_d *last, const char *hist)
{
	t_hist		*h;
	int			fd;

	if (env_getenv((const char **)singleton_env()->environ, "HISTFILE", NULL))
	{
		h = singleton_hist();
		if ((fd = open((hist) ? hist : histfile(), O_RDWR | O_APPEND)) == -1)
		{
			investigate_error(1, "open", NULL, -1);
			return ;
		}
		if (!last)
			last = (!h->last_read) ? NULL : h->last_read;
		while (last)
		{
			write_to_hist((((t_cmd_node *)last->data)->line), fd);
			write(fd, "\n", 1);
			last = last->prev;
		}
		close(fd);
	}
}

void	routine_node(t_hist *h, t_cmd_node **node)
{
	t_list_d	*list;

	list = ft_double_lst_create(*node);
	if (h->list == NULL)
		h->list = ft_create_head(list);
	else
		ft_double_lst_add(&h->list, list);
}

void			history_append_command_to_list(char *command) //int index
{
	t_hist		*h;
	//t_list_d	*list;
	//char *command;

	h = singleton_hist();
	//command = h->current_cmd->line;
	if (h->current_cmd)
	{
		routine_node(h, &h->current_cmd);
		h->current_cmd = NULL;
	}
	else
	{
		if (command[0] == '\0' || ft_str_is_clr(command))
			return ;
		command[ft_strlen(command) - 1] = 0;
		routine(h, command, -1);
		if (!h->last_read)
			h->last_read = (h->list) ? h->list->first : NULL;
	}
}
