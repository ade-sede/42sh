/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:37 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:31 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "failure.h"
#include "line_editing.h"

/*
**	This function places the cursor both visually and in memory above the
**	characher found at line->buff[dest_i]. The function assumes the cursor is
**	currently well positioned above line->buff[start_i].
*/

size_t	cursor_goto_buff(t_line *line, size_t dest_i, size_t start_i)
{
	t_coor	pos;
	t_coor	dest;

	pos = get_char_visual_coor(line, start_i);
	dest = get_char_visual_coor(line, dest_i);
	if (dest.y > pos.y)
		put_ntermcap("do", (size_t)(dest.y - pos.y));
	else if (pos.y > dest.y)
		put_ntermcap("up", (size_t)(pos.y - dest.y));
	put_termcap("cr");
	put_ntermcap("nd", (size_t)dest.x);
	return (dest_i);
}

void	edit_cursor_pos(void)
{
	unsigned int	pos;
	char			b[4];

	put_termcap("u7");
	read(0, b, 4);
	if (b[3] != ';')
		while (read(0, b, 1) == 1 && *b != ';')
			;
	pos = 0;
	while (read(0, b, 1) == 1 && *b != 'R')
		pos = pos * 10 + (unsigned int)(*b - '0');
	if (pos == singleton_line()->ws_col)
		ft_putchar_fd('\n', 2);
	else if (pos != 1)
	{
		put_termcap("so");
		put_termcap("mr");
		ft_putchar_fd('%', 2);
		put_termcap("se");
		ft_putchar_fd('\n', 2);
	}
}

char	edit_check_cursor(void)
{
	unsigned int	pos;
	char			b[4];

	put_termcap("u7");
	read(0, b, 4);
	if (b[3] != ';')
		while (read(0, b, 1) == 1 && *b != ';')
			;
	pos = 0;
	while (read(0, b, 1) == 1 && *b != 'R')
		pos = pos * 10 + (unsigned int)(*b - '0');
	if (pos != 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
