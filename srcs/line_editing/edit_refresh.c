#include "line_editing.h"
#include "env.h"
#include <stdio.h>
#include "failure.h"
#include "color.h"

/*
**	When using a putstr to write the line to the terminal, the behavior is not
**	consistent when it reaches the last column and the char is a newline.  This
**	function makes sure every character is printed where it should (jumps lines
**	twice when it reaches last col with char newline).
*/

void	term_write_char(t_line *line, size_t i)
{
	if (line->visu_mode)
	{
		if (line->pos < line->visu_start)
			if (i >= line->pos && i < line->visu_start)
				ft_putstr("\e[39;42m");
		if (line->pos >= line->visu_start)
			if (i >= line->visu_start && i < line->pos)
				ft_putstr("\e[39;42m");
	}
	write(2, line->buff + i, 1);
	if (line->visu_mode)
	{
		if (line->pos < line->visu_start)
			if (i >= line->pos && i < line->visu_start)
				ft_putstr("\e[0m");
		if (line->pos >= line->visu_start)
			if (i >= line->visu_start && i < line->pos)
				ft_putstr("\e[0m");
	}
}

void	term_putstr(t_line *line)
{
	size_t	i;
	size_t	x;
	t_coor	pos;
	t_coor	l_pos;
	size_t	nb_newl;

	i = 0;
	x = line->prompt_len;
	while (line->buff[i])
	{
		if (line->buff[i] != '\n')
			term_write_char(line, i);
		else
		{
			pos = get_char_visual_coor(line, i);
			l_pos = get_char_visual_coor(line, i - 1);
			nb_newl = 1;
			if (pos.x == 0 && line->buff[i - 1] != '\n' && l_pos.x != (int)line->ws_col)
				nb_newl = 2;
			write(2, "\n\n", nb_newl);
		}
		++i;
	}
}

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
	/* ft_putstr_fd(line->buff, 2); */
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
