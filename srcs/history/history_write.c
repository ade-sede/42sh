#include "history.h"
#include "failure.h"

#if 0
/* void	history_refresh_command(t_hist *h, char *command) */
/* { */
/* 	write(h->fd, command, ft_strlen(command)); */
/* 	write(h->fd, "\n", 1); */
/* } */

/* void	history_write_last_command(void) */
/* { */
/* 	t_hist		*h; */
/* 	t_list_d	*list; */

/* 	h = singleton_hist(); */
/* 	list = h->list->first; */
/* 	history_refresh_command(h, list->data); */
/* } */
#endif

static int write_to_hist(char *value, int fd)
{
	size_t	i;

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

void	history_write_to_histfile(void)
{
	t_hist		*h;
	t_list_d	*last;
	int			fd;

	h = singleton_hist();
	if ((fd = open(h->file, O_RDWR | O_TRUNC)) == -1)
	{
		investigate_error("open", NULL, -1);
		return ;
	}
	last = (!h->list) ? NULL : h->list->last;
	while (last)
	{
		write_to_hist(last->data, fd);
		write(fd, "\n", 1);
		last = last->prev;
	}
	close(fd);
}

void	history_append_command_to_list(char *command)
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
