#include "t_history.h"
#include "libft.h"
#include "failure.h"

/*
**	Be careful to call this function with the rights arguments.  If you
**	want to append the lines newly appended to the list, start must be
**	histfile->last_cmd->next.  Otherwise it must be list->first.
*/

int	history_write_file(t_list_d *start, size_t *ln, const char *filename, int append)
{
	int	flag;
	int	fd;
	t_hist_cmd_node cmd_node;
	t_hist_node		*histnode;
	size_t			i;

	flag = (!append) ? O_WRONLY | O_TRUNC : O_WRONLY | O_APPEND;
	if ((fd = open(filename, flag | O_CREAT, 644)) < 0)
		return (investigate_error(1, "open", NULL, 0));
	while (start)
	{
		++(*ln);
		i = 0;
		histnode = start->data;
		cmd_node = histnode->history;
		while (cmd_node.line.str[i])
		{
			if (cmd_node.line.str[i] == '\n')
			{
				++(*ln);
				write(fd, "\\", 1);
			}
			write(fd, cmd_node.line.str + i, 1);
			++i;
		}
		start = start->next;
	}
	return (1);
}
