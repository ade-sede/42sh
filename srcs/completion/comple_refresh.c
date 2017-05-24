#include "completion.h"
#include "line_editing.h"

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
}

void	comple_refresh_elem(t_comple c, int indice)
{
	if (indice == c.pos)
		put_termcap("mr");
	ft_putstr_padding_space(c.matches[indice], c.max_len);
	put_termcap("me");
	write(1, "  ", 2);
}

void	comple_line_refresh(t_line *line, t_comple c)
{
(void)line;
(void)c;
	/*
	size_t	n;

	put_termcap("cr");
	put_termcap("dl");
	put_prompt(NULL);
	ft_putnstr(line->buff, line->pos);
	if (c.pos != -1)
		ft_putstr(c.matches[c.pos]);
	ft_putstr(line->buff + line->pos);
	n = line->len - line->pos;
	if (c.pos != -1)
		n += ft_strlen(c.matches[c.pos]);
	put_ntermcap("le", n);

*/
}

int	comple_refresh(t_line *line, t_comple c)
{
	size_t	co;
	size_t	li;

	move_cursor_lastline(line);
	//comple_clear(c);
	li = 0;
	while (li < c.nb_lines)
	{
		co = 0;
		put_termcap("do");
		put_termcap("cr");
		while (co < c.nb_colones && co * c.nb_lines + li < c.nb_matches)
		{
			//goto_termcap("ch", co, 0);
			comple_refresh_elem(c, co * c.nb_lines + li);
			co++;
		}
		li++;
	}
	put_ntermcap("up", c.nb_lines);
	move_cursor_bufflen_from_lastline(line);
	edit_refresh_cursor(line);
	//comple_line_refresh(line, c);
	return (1);
}
