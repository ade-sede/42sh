# include "completion.h"
# include "line_editing.h"


int		comple_right(t_comple *c)
{
	c->pos += c->nb_lines;	
	return (1);
}

int		comple_left(t_comple *c)
{
	c->pos -= c->nb_lines;
	return (1);
}

int		comple_up(t_comple *c)
{
	c->pos -= 1;
	return (1);
}

int		comple_down(t_comple *c)
{
	c->pos += 1;
	return (1);
}

