#include "line_editing.h"

void	edit_refresh_cursor(t_line *line)
{
	size_t	src_col;
	size_t	src_line;
	size_t	dest_line;
	size_t	dest_col;
	size_t	ws_col;

	ws_col = line->ws_col;
	src_col = (line->len + 2) % (ws_col - 1);
	dest_col = (line->pos + 2) % (ws_col - 1);
	src_line = (line->len + 2) / (ws_col - 1);
	dest_line = (line->pos + 2) / (ws_col - 1);
	put_ntermcap("up", src_line - dest_line);
	if (dest_col > src_col)
	{
		put_ntermcap("nd", dest_col - src_col);
		//ft_putnbr(dest_col - src_col);
	}
	else 
	{
		put_ntermcap("le", src_col - dest_col);
		//ft_putnbr(src_col - dest_col);
	}
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
		put_termcap("cr");
		ft_putnstr(singleton_line()->buff + i, ws_col - 1);
		i += ws_col - 1;
	}
	if ((line->len + 2) % (ws_col - 1) == 0)
		put_termcap("do");

	//put_termcap("le");
	//put_termcap("up");
}

void	edit_refresh_clear(t_line *line)
{
	size_t	init_line;

	init_line = (line->old_pos + 2) / (line->ws_col - 1);
	put_ntermcap("up", init_line);
	put_termcap("cr");
	//put_ntermcap("dl", init_line);
	put_termcap("cd");
	//put_termcap("do");
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
