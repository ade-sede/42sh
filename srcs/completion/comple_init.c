#include "completion.h"
#include "line_editing.h"

t_comple	*singleton_comple()
{
	static t_comple c;

	return (&c);
}

int	comple_init_winch(t_comple *c)
{
	unsigned int	n;

	n = c->nb_matches;
	c->ws_col = get_ws_col();
	c->nb_colones = get_ws_col() / (c->max_len + 2);
	c->nb_lines = (n % c->nb_colones == 0) ? n / c->nb_colones : (n / c->nb_colones) + 1;
	return (1);
}

int	comple_init(t_line *line, t_comple *c)
{
	c->matches = comple_file_matches(line);
	c->max_len = ft_arraymax_f((const char**)c->matches, ft_strlen);
	c->nb_matches = ft_arraylen((const char**)c->matches);
	comple_init_winch(c);
	c->pos = -1;
	if (c->nb_matches == 1)
	{
		c->pos = 0;
		comple_exit_matched(line, *c);
		return (0);
	}
	return (1);
}
