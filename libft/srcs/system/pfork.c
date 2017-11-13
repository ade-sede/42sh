#include "system.h"

int		p_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror ("fork");
		exit (1);
	}
	return (pid);
}
