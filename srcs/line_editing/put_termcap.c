#include "line_editing.h"

int	int_putchar(int c)
{
	ft_putchar((char)c);
	return (0);
}

void	put_termcap(char *capacity)
{
	tputs(tgetstr(capacity, NULL), 1, int_putchar);
}
