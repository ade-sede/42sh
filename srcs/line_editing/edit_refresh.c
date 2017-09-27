#include "line_editing.h"
#include "env.h"
#include <stdio.h>
#include "failure.h"

void	edit_refresh_cursor(t_line *line)
{
	cursor_goto_buff(line, line->pos, line->len);
}

/*
** Refresh line write buff on multiple lines per ws_col.  If the cursor is in
** the last colomn, move it to the next line.
*/

void	edit_refresh_line(t_line *line)
{
	t_coor pos;

	ft_putstr_fd(line->buff, 2);
	pos = get_char_visual_coor(line, line->len);
	if (pos.x == 0)
		put_termcap("do");
	/* if ((((line->prompt_len + line->pos)) % line->ws_col) == line->ws_col - 1) */
	/* 	put_termcap("do"); */
}

void	edit_refresh_clear(t_line *line)
{
	t_coor	old_pos;

	//	put_ntermcap("up", (line->old_pos + line->prompt_len) / line->ws_col);
	old_pos = get_char_visual_coor(line, line->old_pos);
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
