#include "history.h"
#include "libft.h"
#include "line_editing.h"
#include <stdio.h>

void	history_refresh_line(t_line *line, const char *new)
{
	size_t	len;


	len = ft_strlen(new);
	edit_refresh_clear(line);
	ft_strclr(line->buff);
	if (line->len + len >= line->size)
		realoc_line_buff(line, line->len + len + 1);
	ft_memcpy(line->buff, new, len);
	put_prompt(line);
	edit_refresh_line(line);
	line->pos = len;
	edit_refresh_cursor(line);
	line->pos = len - 1;
}
