#include "history.h"
#include "builtin.h"
#include "env.h"
#include <stdio.h>
#include "get_next_line.h"

const char	**handle_r(t_hist *h, const char **argv, int *error)
{
	char	*filename;
	char	*line;
	t_list_d	*node;
	int		fd;

	line = NULL;
	if (*argv == NULL)
		filename = h->file;
	else
		filename = (char*)*argv;
	if ((fd = open(filename, O_RDONLY)) == -1)
		*error = return_failure("Failed to open the file ", filename);
	if (*error == EXIT_SUCCESS && fd != -1)
	{
		while (get_next_line(fd, &line))
		{
			printf("%s\n", line);//			REMOVE		
			node = ft_double_lst_create(line);
			printf("1\n");//			REMOVE		
			if (!h->list)
			{
				h->list = ft_create_head(node);
				printf("2\n");//			REMOVE		
			}
			else
			{
				ft_double_lst_add(&(h->list), node);
				printf("3\n");//			REMOVE		
			}
		}
		printf("in\n");//			REMOVE		
		close(fd);
	}
	return ((*argv == NULL) ? argv : argv + 1);
}
