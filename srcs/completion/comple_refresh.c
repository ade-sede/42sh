#include "completion.h"
#include "line_editin.h"

void	comple_refresh_elem(t_comple c, int indice)
{
	ft_putstr(c.matches[indice]);
}

void	comple_line_refresh(t_line *line, t_comple c);
{
	put_termcap("cr");
	put_termcap("dl");
	put_prompt(env);
	ft_putnstr(line->pos, line->pos);
	ft_putstr(c.matches[pos]);
	ft_putstr(line->pos + line->pos);
	n = line()->len - line()->pos;
	put_ntermcap("le", n + ft_strlen(c.matches[pos]));
}

int	comple_refresh(t_line *line, t_comple c)
{
	int		co;
	int		li;

	put_termcap("do");
	put_termcap("cr");
	li = 0;
	while (li < c.nb_lines)
	{
		co = 0;
		while (co < c.nb_lines + li)
		{
			goto_termap("ch", co, 0);
			comple_refresh_elem(c, co * c.nb_lines + li);
			co++;
		}
		put_termcap("do");
		put_termcap("cr");
		li++;
	}
	put_ntermcap("up", c.nb_lines);
	comple_line_refresh(line, c);
}
