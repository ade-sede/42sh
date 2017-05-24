#include "line_editing.h"

void	edit_refresh_cursor(t_line *line)
{
	size_t	src_col;
	size_t	src_line;
	size_t	dest_line;
	size_t	dest_col;
	size_t	ws_col;

	ws_col = line->ws_col;
	src_col = (line->len + line->prompt_len) % (ws_col);
	dest_col = (line->pos + line->prompt_len) % (ws_col);
	src_line = (line->len + line->prompt_len) / (ws_col);
	dest_line = (line->pos + line->prompt_len) / (ws_col);
	put_ntermcap("up", src_line - dest_line);
	if (dest_col > src_col)
		put_ntermcap("nd", dest_col - src_col);
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
	ft_putnstr(line->buff, ws_col - line->prompt_len);
	i = ws_col - line->prompt_len;
	while (i < line->len)
	{
		put_termcap("do");
		put_termcap("cr");
		ft_putnstr(singleton_line()->buff + i, ws_col);
		i += ws_col;
	}
	/*
	**if the cursor is in the last colomn, move it to the next line.
	*/
	if ((line->len + line->prompt_len) % (ws_col) == 0)
		put_termcap("do");
}

void	edit_refresh_clear(t_line *line)
{
	put_ntermcap("up", (line->old_pos + line->prompt_len) / line->ws_col);
	put_termcap("cr");
	//put_ntermcap("dl", init_line);
	put_termcap("cd");
	//put_termcap("do");
}

void	edit_refresh(t_line *line)
{
	//ft_putchar('\n');
	//put_termcap("up");
	edit_refresh_clear(line);
	//put_termcap("do");
	//put_termcap("dl");
	line->prompt_len = put_prompt(NULL);
	edit_refresh_line(line);
	edit_refresh_cursor(line);
}
