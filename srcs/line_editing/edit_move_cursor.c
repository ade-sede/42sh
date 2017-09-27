#include "line_editing.h"

void	move_cursor_lastline(t_line *line)
{
	cursor_goto_buff(line, line->len, -1);
	/* put_ntermcap("do", ((line->len - 1 + line->prompt_len) / line->ws_col) \ */
	/* 		- (line->pos + line->prompt_len) / line->ws_col); */
	put_termcap("cr");
}

void	move_cursor_lastline_from_first_line(t_line *line)
{
	cursor_goto_buff(line, line->len, 0);
	/* put_ntermcap("do", ((line->len - 1 + line->prompt_len) / line->ws_col) \ */
	/* 		- (0 + line->prompt_len) / line->ws_col); */
	put_termcap("cr");
}

void	move_cursor_firstline_from_lastline(t_line *line)
{
	cursor_goto_buff(line, 0, line->len);
	/* put_ntermcap("up", ((line->len - 1 + line->prompt_len) / line->ws_col) \ */
	/* 		- (line->prompt_len) / line->ws_col); */
	put_termcap("cr");
}

void	move_cursor_firstline_from_prev_pos(t_line *line)
{
	cursor_goto_buff(line, 0, line->old_pos);
	/* put_ntermcap("up", ((line->old_pos - 1 + line->prompt_len) / line->ws_col) \ */
	/* 		- (line->prompt_len) / line->ws_col); */
	put_termcap("cr");
}

void	move_cursor_bufflen_from_lastline(t_line *line)
{
	put_termcap("cr");
	put_ntermcap("nd", (line->len + line->prompt_len) % (line->ws_col));
}
