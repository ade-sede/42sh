#include "line_editing.h"

int		int_putchar(int c)
{
	ft_putchar_fd((char)c, 2);
	return (0);
}

void	put_termcap(char *capacity)
{
	tputs(tgetstr(capacity, NULL), 1, int_putchar);
}

void	put_ntermcap(char *capacity, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		put_termcap(capacity);
		i++;
	}
}
