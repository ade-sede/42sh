#ifndef HISTORY_H
# define HISTORY_H
# include "t_history.h"
# include "t_line.h"

int		history_get_input(t_line *line, t_history *history, unsigned long keycode);
int		history_read_file(t_lst_head **head, const char *filename, size_t *ln, t_list_d **last_cmd);
int		history_write_file(t_list_d *start, size_t *ln, const char *filename, int append);
int		history_write_file_wrapper(t_history *history, const char *filename, int append);
int		history_push(t_lst_head **head, t_list_d *node);
int		history_init(t_history *hist);
void	free_history_node(t_list_d **node);
int		history_prev(t_line *line, t_history *history);
int		history_next(t_line *line, t_history *history);
void	history_refresh_line(t_line *line, const char *new);
#endif
