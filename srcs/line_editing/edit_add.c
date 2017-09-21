#include "line_editing.h"
#include "failure.h"
#include "color.h"

void	realoc_line_buff(char **buff, unsigned int *size, \
		unsigned int size_needed)
{
	char			*new;
	unsigned int	new_size;

	new_size = (size_needed / BUFF_LINE_SIZE + 2) * BUFF_LINE_SIZE;
	new = ft_strnew(new_size);
	ft_strcpy(new, *buff);
	free(*buff);
	*buff = new;
	*size = new_size;
}

void	edit_add(int keycode, t_line *line)
{



	/* t_coor	pos_after_write; */
	/* t_coor	pos_before_write; */
	/* int		diff_number; */

	/* diff_number = 0; */
	if (line->len >= line->size)
		realoc_line_buff(&line->buff, &line->size, line->len + 1);
	if (line->pos == line->len)
		line->buff[line->len] = (char)keycode;
	else
	{
		ft_memmove((void*)(line->buff + line->pos + 1), \
				(void*)(line->buff + line->pos), line->len - line->pos);
		line->buff[line->pos] = (char)keycode;
	}
	/* Write line from where it changed */
//	ft_putstr_fd(line->buff + line->pos, 2);
	/* Update memory infos */
	line->pos++;
	line->len++;
	edit_refresh(line);
}
