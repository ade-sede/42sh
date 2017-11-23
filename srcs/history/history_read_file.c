#include "history.h"
#include "libft.h"
#include "failure.h"
#include "get_next_line.h"
#include <stdio.h>

static int	concat(char *line, char **cat)
{
	if (*cat)
	{
		(*cat)[ft_strlen(*cat) - 1] = '\n';
		*cat = ft_strjoin_free(*cat, line, 0b11); }
	if (!*cat)
		*cat = line;
	return (1);
}

static int	skip_lines(size_t *ln, int fd)
{
	char	*line;
	size_t	index;

	index = 0;
	while (index != *ln && get_next_line(fd, &line))
	{
		ft_strdel(&line);
		++index;
	}
	if (index != *ln)
		*ln = index;
	return (1);
}

static int push_routine(t_lst_head **head, char *line, t_list_d **last_cmd)
{
	t_list_d	*new_node;
	t_hist_node	*hist_node;

	hist_node = create_hist_node();
	update_line_hist_cmd_node(&hist_node->history, line);
	copy_cmd_node(&hist_node->history, &hist_node->hist_modif);
	new_node = ft_double_lst_create(hist_node);
	history_push(head, new_node);
	*last_cmd = new_node;
	return (1);
}


/* static int	print_history(t_list_d *first) */
/* { */
/* 	t_hist_node *node; */
/* 	while (first) */
/* 	{ */
/* 		node = first->data; */
/* 		dprintf(2, "#%s#\n", node->history.line.str); */
/* 		first = first->next; */
/* 	} */
/* 	return (1); */
/* } */
int		history_read_file(t_lst_head **head, const char *filename, size_t *ln, t_list_d **last_cmd)
{
	int		fd;
	char	*line;
	char	*cat;

	cat = NULL;
	if ((fd = open(filename, O_RDONLY)) < 0)
		return (investigate_error(0, "open", NULL, 0));
	skip_lines(ln, fd);
	while (get_next_line(fd, &line))
	{
		++(*ln);
		if (!cat && !*line)
		{
			free(line);
			continue ;
		}
		concat(line, &cat);
		if (charcmp(cat, ft_strlen(cat) - 1, '\\'))
			continue ;
		/* Pushback command to the end of the history */
		push_routine(head, cat, last_cmd);

		cat = NULL;
	}
	close(fd);
	return (1);
}
