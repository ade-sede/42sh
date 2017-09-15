#include "completion.h"
#include "line_editing.h"
#include <stdio.h>

void	ft_putstr_padding_space(char *str, unsigned int size)
{
	unsigned int len;

	len = ft_strlen_color(str);
	ft_putstr_fd(str, 2);
	while ((size - len) > 0)
	{
		write(2, " ", 1);
		size--;
	}
}

void	comple_refresh_elem(t_comple c, int indice)
{
	char	*word;

	if (indice == c.pos)
	{
		put_termcap("mr");
		word = extract_color(c.matches[indice]);
		ft_putstr_padding_space(word, c.max_len);
		free(word);
	}
	else
		ft_putstr_padding_space(c.matches[indice], c.max_len);
	put_termcap("me");
	write(2, "  ", 2);
}

void	comple_refresh_line(t_line *line, t_comple c)
{
	put_ntermcap("up", c.nb_lines);
	move_cursor_firstline_from_lastline(line);
	put_prompt(line);
	edit_refresh_line(line);
	edit_refresh_cursor(line);
}

size_t	comple_listart_big_completion(t_comple c)
{
	if (c.pos == -1)
		return (0);
	else
		return (c.pos % c.nb_lines / (c.ws_row - 1)) * (c.ws_row - 1);
}

int		comple_refresh(t_line *line, t_comple c)
{
	size_t	co;
	size_t	li;
	size_t	li_start;

	put_termcap("cd");
	li_start = 0;
	if (c.nb_lines > c.ws_row)
		li_start = comple_listart_big_completion(c);
	move_cursor_lastline(line);
	li = li_start;
	while (li < c.nb_lines && li - li_start < c.ws_row - 1)
	{
		co = 0;
		put_termcap("do");
		put_termcap("cr");
		while (co < c.nb_colones && co * c.nb_lines + li < c.nb_matches)
		{
			comple_refresh_elem(c, co * c.nb_lines + li);
			co++;
		}
		li++;
	}
	comple_refresh_line(line, c);
	return (1);
}
