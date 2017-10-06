#include "line_editing.h"
#include "env.h"
#include <stdio.h>
#include "failure.h"
#include "color.h"

/* void	write_to_term(t_line *line) */
/* { */
/* 	size_t	i; */
/* 	size_t	x; */

/* 	i = 0; */
/* 	x = line->prompt_len; */
/* 	while (line->buff[i]) */
/* 	{ */
/* 		if (x == line->ws_col) */
/* 		{ */
/* 			write(2, "\n", 1); */
/* 			x = 0; */
/* 		} */
/* #if 0 */
/* 		if (line->visu_mode) */
/* 		{ */
/* 			if (line->pos < line->visu_start) */
/* 				if (i >= line->pos && i < line->visu_start) */
/* 					ft_putstr("\e[39;42m"); */
/* 			if (line->pos >= line->visu_start) */
/* 				if (i >= line->visu_start && i < line->pos) */
/* 					ft_putstr("\e[39;42m"); */
/* 		} */
/* #endif */
/* 		write(2, line->buff + i, 1); */
/* #if 0 */
/* 		if (line->visu_mode) */
/* 		{ */
/* 			if (line->pos < line->visu_start) */
/* 				if (i >= line->pos && i < line->visu_start) */
/* 					ft_putstr("\e[0m"); */
/* 			if (line->pos >= line->visu_start) */
/* 				if (i >= line->visu_start && i < line->pos) */
/* 					ft_putstr("\e[0m"); */
/* 		} */
/* #endif */
/* 		++i; */
/* 		++x; */
/* 	} */
/* } */

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
	if (pos.x == 0 && (line->pos != 0 && line->buff[line->pos - 1] != '\n') )
		put_termcap("do");
}

void	edit_refresh_clear(t_line *line)
{
	cursor_goto_buff(line, 0, line->old_pos);
	put_termcap("cr");
	put_termcap("cd");
}

void	edit_refresh(t_line *line)
{
	edit_refresh_clear(line);
	put_prompt(line);
	/* line->visu_mode ? edit_refresh_visu(line) : edit_refresh_line(line); */
	edit_refresh_line(line);
	edit_refresh_cursor(line);
}
