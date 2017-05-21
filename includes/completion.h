#ifndef COMPLETION_H
# define COMPLETION_H
# include "line_editin.h"

typedef struct		s_comple
{
	char		**matches;
	int		pos;
	size_t		ws_col;
	size_t		nb_lines;
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

# endif
