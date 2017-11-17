#include "line_editing.h"
#include "failure.h"
#include "color.h"

void	realoc_line_buff(t_line *line, size_t new_size)
{
	line->buff = cl_realloc(line->size, line->buff, new_size);
	line->size = new_size;
	/* char			*new; */
	/* unsigned int	new_size; */

	/* new_size = (size_needed / BUFF_LINE_SIZE + 2) * BUFF_LINE_SIZE; */
	/* new = ft_strnew(new_size); */
	/* ft_strcpy(new, *buff); */
	/* free(*buff); */
	/* *buff = new; */
	/* *size = new_size; */
}

void	edit_add(int keycode, t_line *line)
{
	if (line->len == line->size - 1)
		realoc_line_buff(line, line->size + BUFF_LINE_SIZE);
	/* if (line->pos == line->len) */
	/* 	line->buff[line->len] = (char)keycode; */
	/* else */
	/* { */
		ft_memmove((void*)(line->buff + line->pos + 1), \
				(void*)(line->buff + line->pos), line->len - line->pos);
		line->buff[line->pos] = (char)keycode;
	/* } */
	line->pos++;
	line->len++;
	edit_refresh(line);
}
