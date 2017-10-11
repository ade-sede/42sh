#include <sys/ioctl.h>
#include <stdlib.h>
#include "line_editing.h"
#include "failure.h"

size_t				get_ws_col(void)
{
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	return (w.ws_col);
}

size_t				get_ws_row(void)
{
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	return (w.ws_row);
}

size_t				get_reserved_line(size_t ws_row, t_line *line)
{
	size_t	used_by_prompt;
	size_t	used_by_buff;

	used_by_prompt = (size_t)get_prompt_visual_offset(line).y;
	used_by_buff = (size_t)get_char_visual_coor(line, line->len).y;
	logwrite("log/def", __func__, "%zu\n", ws_row - used_by_prompt -
			used_by_buff);
	return (ws_row - used_by_prompt - used_by_buff);
}
