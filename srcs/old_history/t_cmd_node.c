#include "history.h"
#include "libft.h"


t_hist_cmd_node	*create_hist_cmd_node(const char *line, int index)
{
	t_hist_cmd_node *ret;

	ret = ft_memalloc(sizeof(t_hist_cmd_node));
	ret->index = index;
	gettimeofday(&ret->timestamp, NULL);
	ret->line = ft_strdup(line);
	return (ret);
}

void	free_hist_cmd_node(void *ptr)
{
	t_hist_cmd_node *node;

	node = ptr;
	free((void*)node->line);
	free(node);
}
