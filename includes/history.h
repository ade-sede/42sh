#ifndef HISTORY_H
# define HISTORY_H
# include "libft.h"
# include "line_editing.h"


typedef struct	s_hist
{
	char		*file;
	t_lst_head	*list;
	t_list_d		*cur;
}		t_hist;

t_hist	*singleton_hist(void);
int	history_load(t_hist *h);
void	history_init(t_hist *h);

int	history_prev(t_line *line);
int	history_next(t_line *line);
# endif
