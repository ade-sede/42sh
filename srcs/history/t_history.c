#include "t_history.h"
#include "failure.h"
#include "environ.h"
#include "libft.h"
#include <sys/time.h>
#include "get_next_line.h"

void		concat(char *line, char **cat)
{
	if (*cat)
	{
		(*cat)[ft_strlen(*cat) - 1] = '\n';
		*cat = ft_strjoin_free(*cat, line, 0b11);
	}
	if (!*cat)
		*cat = line;
}

int         history_load(t_history *hist)
{
	int         fd;
	char        *line;
	char        *cat;

	cat = NULL;
	init_history(hist);
	if ((fd = open(histfile(), O_RDWR | O_CREAT, 0644)) == -1)
		return (0);
	while (get_next_line(fd, &line))
	{
		++hist->history_line;
		if (!cat && !*line)
		{
			free(line);
			continue ;
		}
		concat(line, &cat);
		if (charcmp(cat, ft_strlen(cat) - 1, '\\'))
			continue ;
		set_new_hist_cmd(hist, cat);
		ft_putendl(cat);
		cat = NULL;
	}
	close(fd);
	return (1);
}
