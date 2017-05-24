#include "line_editing.h"

void	edit_refresh_cursor(t_line *line)
{
	size_t	src_col;
	size_t	src_line;
	size_t	dest_line;
	size_t	dest_col;
	size_t	ws_col;

	ws_col = line->ws_col;
	src_col = (line->len + 2) % ws_col;
	dest_col = (line->pos + 2) % ws_col;
	src_line = (line->len + 2) / ws_col;
	dest_line = (line->pos + 2) / ws_col;
	put_ntermcap("up", src_line - dest_line);
	if (dest_col > src_col)
		put_ntermcap("ri", dest_col - src_col);
	else 
		put_ntermcap("le", src_col - dest_col);
}
/*
** refresh line write buff on multiple lines per ws_col.
*/

void	edit_refresh_line(t_line *line)
{
	size_t	i;
	size_t	ws_col;

	ws_col = line->ws_col;
	ft_putnstr(line->buff, ws_col - 2 - 1);
	i = ws_col - 2 - 1;
	while (i < line->len)
	{
		put_termcap("do");
		ft_putnstr(singleton_line()->buff + i, ws_col - 1);
		i += ws_col - 1;
	}
	//put_termcap("up");
}

void	edit_refresh_clear(t_line *line)
{
	size_t	init_line;

	init_line = (line->pos + 2) / line->ws_col;
	put_ntermcap("up", init_line);
	put_termcap("cr");
	put_termcap("cd");
}

void	edit_refresh(int signum, t_env *env)
{
	t_line	*line;

	line = singleton_line();
	//ft_putchar('\n');
	//put_termcap("up");
	edit_refresh_clear(line);
	//put_termcap("do");
	//put_termcap("dl");
	put_prompt(env);
	edit_refresh_line(line);
	edit_refresh_cursor(line);
	(void)signum;
}
