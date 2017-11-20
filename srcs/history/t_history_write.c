#include "failure.h"
#include <fcntl.h>
#include "t_history.h"

static int      write_to_hist(char *value, int fd)
{
	size_t      i;

	i = 0;
	while (*(value + i))
	{
		if (*(value + i) == '\n')
			write(fd, "\\", 1);
		write(fd, value + i, 1);
		++i;
	}
	return (1);
}

void            history_write_to_histfile(t_history *hist, t_list_d *last)
{
	int         fd;

	if (!hist)
		hist = singleton_history();
	if (!last)
		last = hist->command_list->last;
	if ((fd = open(histfile(), O_RDWR | O_APPEND)) == -1)
	{
		investigate_error(1, "open", NULL, -1);
		return ;
	}
	while (last)
	{
		write_to_hist((((t_hist_node *)last->data)->history.line), fd);
		write(fd, "\n", 1);
		last = last->prev;
	}
	close(fd);
}

