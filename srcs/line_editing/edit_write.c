#include "line_editing.h"
#include "t_env.h"
#include <stdio.h>
#include "failure.h"
#include "color.h"

/*
**	When using a putstr to write the line to the terminal, the behavior is not
**	consistent when it reaches the last column and the char is a newline.  This
**	function makes sure every character is printed where it should (jumps lines
**	twice when it reaches last col with char newline).
*/

static void	term_write_char(t_line *line, size_t i)
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
	if (((line->read).flags & S))
		write(2, "*", 1);
	else
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

void		term_putstr(t_line *line)
{
	size_t	i;
	t_coor	pos;
	t_coor	l_pos;
	size_t	nb_newl;

	i = 0;
	while (line->buff[i])
	{
		if (line->buff[i] != '\n')
			term_write_char(line, i);
		else
		{
			pos = get_char_visual_coor(line, i);
			l_pos = get_char_visual_coor(line, i - 1);
			nb_newl = 1;
			if (pos.x == 0 && line->buff[i - 1] != '\n' &&
					l_pos.x != (int)line->ws_col)
				nb_newl = 2;
			write(2, "\n\n", nb_newl);
		}
		++i;
	}
}
