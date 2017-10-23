#include "line_editing.h"

int		control_l(t_line *line)
{
	put_termcap("cl");
	edit_refresh(line);
	return (1);
}
