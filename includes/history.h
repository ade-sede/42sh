#ifndef HISTORY_H
# define HISTORY_H
# include "libft.h"
# include "line_editing.h"
# include "fcntl.h"

typedef struct	s_hist
{
	char		*file;
	t_lst_head	*list;
	t_list_d	*cur;
	char		*writen_buff;
	t_lst_head	*btsearch_list;
	t_list_d	*btsearch_cur;
	char		*btsearch_buff;
	size_t		btsearch_buff_len;
	int			signum;
	int			fd;
}				t_hist;

t_hist			*singleton_hist(void);
int				history_load(t_hist *h, t_env *env);

int				history_get_input(t_line *line, unsigned long keycode);
void			history_init(t_hist *h);
int				history_move_exit(t_line *line, t_hist *hist);
int				history_move_init(t_line *line, t_hist *hist);
int				history_move_exit(t_line *line, t_hist *hist);
int				history_next(t_line *line, t_hist *h);
int				history_prev(t_line *line, t_hist *h);

/*
** fonction du backtracking search avec <C-R>
*/

int				btsearch_get_input(t_line *line, unsigned long keycode);
int				btsearch_init(t_line *line, t_hist *h);
int				btsearch_exit(t_line *line, t_hist *hist);
int				btsearch_init(t_line *line, t_hist *hist);
void			btsearch_add(char keycode, t_line *line, t_hist *h);
int				btsearch_prev(t_line *line, t_hist *h);
int				btsearch_next(t_line *line, t_hist *h);
void			btsearch_refresh(t_line *line, t_hist *h);
void			btsearch_change_line(t_line *line, t_hist *h, t_list_d *node);
int				btsearch_handle_sigwinch(t_line *line, t_hist *h);
void			btsearch_handle_sigint(int keycode);
void			btsearch_handle_signals(void);
void			btsearch_del(t_line *line, t_hist *h);
void			btsearch_first_search(t_hist *h);
void			create_strstr_btsearch_buff(t_list_d *item);

void			history_append_command_to_list(char *command);
void			history_write_to_histfile(void);
void			history_line_refresh(t_line *line, char *new_line);

/*
** void			history_write_last_command();
*/

#endif
