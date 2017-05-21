#include "completion.h"
#include "line_editin.h"

void	ft_putstr_padding_space(char *str, unsigned int size)
{
	unsigned int len;

	len = ft_strlen(str);
	ft_putstr(str);
	while ((size - len) > 0)
	{
		write(1, " ", 1);
		size--;
	}
	write(1, " ", 1);
}

void	comple_refresh_elem(t_comple c, int indice)
{
	if (indice = c.pos)
		put_termcap("mr");
	ft_putstr_padding_space(c.matches[indice], c.maxlen);
	put_termcap("me");
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
