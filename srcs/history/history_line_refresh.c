#include "history.h"
#include "line_editing.h"

void	history_line_refresh(t_line *line, char *new_line)
{
	ft_strclr(line->buff);
	edit_insert_str(line, line->buff, new_line);
	line->len = ft_strlen((const char *)new_line);
	line->pos = line->len;
	edit_refresh(line);
}
