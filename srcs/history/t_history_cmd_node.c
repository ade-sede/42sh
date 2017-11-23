#include "libft.h"
#include "t_history.h"
#include <sys/time.h>

void	update_timestamp(t_hist_cmd_node *node)
{
	gettimeofday(&node->timestamp, NULL);
}

void	update_line_hist_cmd_node(t_hist_cmd_node *node, const char *line)
{
	w_free(&node->line);
	w_newword(&node->line);
	w_addstr(&node->line, line);
	node->modified = 1;
}

void	append_line_hist_cmd_node(t_hist_cmd_node *node, const char *cat)
{
	w_addstr(&node->line, cat);
	node->modified = 1;
}

void	insert_char_hist_cmd_node(t_hist_cmd_node *node, size_t index, const char c)
{
	w_insertchar(&node->line, c, index);
	node->modified = 1;
}

void	insert_line_hist_cmd_node(t_hist_cmd_node *node, const char *cat, size_t index)
{
	w_insertstr(&node->line, cat, index);
	node->modified = 1;
}

void	append_char_hist_cmd_node(t_hist_cmd_node *node, const char c)
{
	w_addchar(&node->line, c);
	node->modified = 1;
}

void	index_hist_cmd_node(t_hist_cmd_node *node, size_t index)
{
	node->index = index;
	node->modified = 1;
}

void	destroy_hist_cmd_node(t_hist_cmd_node *node)
{
	w_free(&node->line);
	ft_bzero(node, sizeof(*node));
}
