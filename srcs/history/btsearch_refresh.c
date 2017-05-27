#include "line_editing.h"
#include "history.h"

void	btsearch_refresh(t_line *line, t_hist *h)
{
	edit_refresh(line);
	(void)h;
}
