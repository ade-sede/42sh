#include "line_editing.h"

void	move_cursor_lastline(t_line *line)
{
	put_ntermcap("do", ((line->len -1 + 2) / line->ws_col) - (line->pos + 2) / line->ws_col);
	put_termcap("cr");
}

void	move_cursor_bufflen_from_lastline(t_line *line)
{
	put_termcap("cr");
	put_ntermcap("nd", (line->len + 2) % (line->ws_col));
}
