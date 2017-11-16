#include "line_editing.h"
#include "failure.h"

int		verbatim(t_line *line)
{
	line->verbatim = 1;
	ft_putchar_fd('^', 2);
	put_termcap("le");
	return (1);
}
