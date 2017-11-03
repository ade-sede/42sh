#include <signal.h>
#include <stdio.h>

void		handler(int		signum)
{
	printf("%d\n", signum);
}

int		main()
{
	int		i = 1;

	while (i <= 31)
	{
		signal(i, handler);
		i++;
	}
	while (1)
		;
}
