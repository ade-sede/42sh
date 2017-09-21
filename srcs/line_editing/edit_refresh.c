#include "line_editing.h"
#include "env.h"
#include <stdio.h>
#include "failure.h"

void	edit_refresh_cursor(t_line *line)
{
	size_t	src_col;
	size_t	src_line;
	size_t	dest_line;
	size_t	dest_col;
	size_t	ws_col;

	t_coor src;
	t_coor dest;
	if (!ft_strchr(line->buff, '\n'))
	{
		src =  get_char_visual_coor(line, line->buff + line->len);
		dest = get_char_visual_coor(line, line->buff + line->pos);
		src_col = src.x;
		src_line = src.y;
		dest_col= dest.x;
		dest_line = dest.y;
		logwrite(__func__, "%zu\n%zu\n%zu\n%zu\n", src_col, src_line, dest_col, dest_line);
		ws_col = line->ws_col;
#if 0
		/* src_col = (line->len + line->prompt_len) % (ws_col); */
		/* dest_col = (line->pos + line->prompt_len) % (ws_col); */
		/* src_line = (line->len + line->prompt_len) / (ws_col); */
		/* dest_line = (line->pos + line->prompt_len) / (ws_col); */
#endif
		/* getchar(); */ 
		put_ntermcap("up", src_line - dest_line);
		/* getchar(); */ 
		if (dest_col > src_col)
			put_ntermcap("nd", dest_col - src_col);
		else
			put_ntermcap("le", src_col - dest_col);
	}
}

/*
** Refresh line write buff on multiple lines per ws_col.  If the cursor is in
** the last colomn, move it to the next line.
*/

void	edit_refresh_line(t_line *line)
{
	t_coor pos;

	ft_putstr_fd(line->buff, 2);
	pos = get_char_visual_coor(line, line->buff + line->len);
	if (pos.x == 0)
	{
		put_termcap("do");
		logwrite(__func__, "Reached case\n");
	}
	/* if ((((line->prompt_len + line->pos)) % line->ws_col) == line->ws_col - 1) */
	/* 	put_termcap("do"); */
}

void	edit_refresh_clear(t_line *line)
{
	t_coor	old_pos;

//	put_ntermcap("up", (line->old_pos + line->prompt_len) / line->ws_col);
	old_pos = get_char_visual_coor(line, line->buff + line->old_pos);
	logwrite(__func__, "old_pos.y = %d\n", old_pos.y);//			REMOVE		
	put_ntermcap("up", (size_t)old_pos.y);
	put_termcap("cr");
	put_termcap("cd");
}

void	edit_refresh(t_line *line)
{
	edit_refresh_clear(line);
	put_prompt(line);
	line->visu_mode ? edit_refresh_visu(line) : edit_refresh_line(line);
	edit_refresh_cursor(line);
}
