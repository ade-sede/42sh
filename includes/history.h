#ifndef HISTORY_H
# define HISTORY_H
# include "libft.h"


typedef struct	s_hist
{
	char		*file;
	t_lst_head	*list;
}		t_hist;

t_hist	*singleton_hist(void);
int	history_load(t_hist *h);

# endif
