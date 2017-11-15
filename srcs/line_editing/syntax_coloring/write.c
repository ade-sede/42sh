#include "syntax_coloring.h"
#include "libft.h"

static void	term_write_char(t_line *line, size_t i)
{
	/* if (line->visu_mode) */
	/* { */
	/* 	if (line->pos < line->visu_start) */
	/* 		if (i >= line->pos && i < line->visu_start) */
	/* 			ft_putstr("\e[39;42m"); */
	/* 	if (line->pos >= line->visu_start) */
	/* 		if (i >= line->visu_start && i < line->pos) */
	/* 			ft_putstr("\e[39;42m"); */
	/* } */
	if (line->read_builtin && (line->read->flags & S))
		write(2, "*", 1);
	else
		write(2, line->buff + i, 1);
	/* if (line->visu_mode) */
	/* { */
	/* 	if (line->pos < line->visu_start) */
	/* 		if (i >= line->pos && i < line->visu_start) */
	/* 			ft_putstr("\e[0m"); */
	/* 	if (line->pos >= line->visu_start) */
	/* 		if (i >= line->visu_start && i < line->pos) */
	/* 			ft_putstr("\e[0m"); */
	/* } */
}

void	write_term(t_line *line, size_t i)
{
	t_coor	pos;
	t_coor	l_pos;
	t_coor	tab_pos;
	size_t	offset;
	size_t	nb_newl;

	if (line->buff[i] == '\t')
	{
		tab_pos = get_char_visual_coor(line, i);
		offset = (tab_pos.x % 8) ? (8 - (tab_pos.x % 8)) : 8;
		if (tab_pos.x == 0)	// If pos.x = 0 we need to both jump a line and write a tab
		{
			/* ft_putchar_fd('\n', 2); */
			ft_putchar_fd(' ', 2);
			ft_putchar_fd('\t', 2);
		}
		else if (tab_pos.x + offset >= line->ws_col) // Jump line if tabulation would overflow the window.
		{
			ft_putchar_fd('\t', 2);
			ft_putchar_fd('\n', 2);
			/* if (i == 0 || (i > 0 && line->buff[i - 1] != '\t'))	// 2 tabulation could fit this condition. */
			/* 	ft_putchar_fd('\n', 2); */
		}
		else
		{
			ft_putchar_fd('\t', 2);	// Write tabulation
		}
	}
	else if (line->buff[i] == '\n')
	{
		pos = get_char_visual_coor(line, i);
		l_pos = get_char_visual_coor(line, i - 1);
		nb_newl = 1;
		if (pos.x == 0 && line->buff[i - 1] != '\n' &&
				l_pos.x != (int)line->ws_col)
			nb_newl = 2;
		write(2, "\n\n", nb_newl);
	}
	else
		term_write_char(line, i);
}
