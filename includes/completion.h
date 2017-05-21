#ifndef COMPLETION_H
# define COMPLETION_H
# include "line_editing.h"

typedef struct		s_comple
{
	char		**matches;
	int		pos;
	size_t		ws_col;
	size_t		max_len;
	size_t		nb_lines;
	size_t		nb_colones;
	size_t		nb_matches;
}			t_comple;

typedef struct		s_comple_func
{
	unsigned long long	keycode;
	int			(*f)(t_line *, t_comple *);
}			t_comple_func;

int	comple_init(t_line *line, t_comple *c);
int	comple_get_input(t_env *env);

int		comple_end(t_line *line);
int		comple_home(t_line *line);
int		comple_right(t_line *line);
int		comple_left(t_line *line);
int		comple_up(t_line *line);
int		comple_down(t_line *line);

int	comple_refresh(t_line *line, t_comple c);

void	comple_clear(t_comple c);
void	comple_free(t_comple c);
int	comple_exit_matched(t_line *line, t_comple c);
# endif
