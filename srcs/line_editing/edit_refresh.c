#include "line_editing.h"
#include "t_env.h"
#include <stdio.h>
#include "failure.h"
#include "color.h"

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

	term_putstr(line);
	pos = get_char_visual_coor(line, line->len);
	if (pos.x == 0 && (line->pos != 0 && line->buff[line->pos - 1] != '\n'))
		put_termcap("do");
}

void	edit_refresh_clear(t_line *line)
{
	int		y;

	cursor_goto_buff(line, 0, line->old_pos);
	y = get_prompt_visual_offset(line).y;
	put_ntermcap("up", (size_t)y);
	put_termcap("cr");
	put_termcap("cd");
}

void	edit_refresh(t_line *line)
{
	edit_refresh_clear(line);
	put_prompt(line);
	edit_refresh_line(line);
	edit_refresh_cursor(line);
}
