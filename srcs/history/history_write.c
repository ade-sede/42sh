#include "history.h"
#include "failure.h"

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

void	history_write_to_file(int fd, t_hist *h)
{
	t_list_d	*last;

	last = (!h->list) ? NULL : h->list->last;
	while (last)
	{
		write_to_hist(last->data, fd);
		write(fd, "\n", 1);
		last = last->prev;
	}
}

void			history_write_to_histfile(void)
{
	t_hist		*h;
	int			fd;

	h = singleton_hist();
	if ((fd = open(h->file, O_RDWR | O_TRUNC | O_CREAT, 0644)) == -1)
	{
		investigate_error(1, "open", NULL, -1);
		return ;
	}
	history_write_to_file(fd, h);
	close(fd);
}

void			history_append_command_to_list(char *command)
{
	t_hist		*h;
	t_list_d	*list;

	h = singleton_hist();
	if (command[0] == '\0' || ft_str_is_clr(command))
		return ;
	command[ft_strlen(command) - 1] = 0;
	list = ft_double_lst_create(ft_strdup(command));
	if (h->list == NULL)
		h->list = ft_create_head(list);
	else
		ft_double_lst_add(&h->list, list);
}
