#ifndef HISTORY_H
# define HISTORY_H
# include "t_history.h"

int		history_read_file(t_lst_head **head, const char *filename, size_t *ln, t_list_d **last_cmd);
int		history_write_file(t_list_d *start, size_t *ln, const char *filename, int append);
int		history_push(t_lst_head **head, t_list_d *node);
int		history_init(t_history *hist);
void	free_history_node(t_list_d **node);
#endif
