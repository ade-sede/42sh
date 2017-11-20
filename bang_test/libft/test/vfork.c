#include "libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <wait.h>

int		main(void)
{
	/* pid_t	child; */
	int fd = open("myfile", O_RDWR);
	int	ret;
	if (fd < 0)
	{
		perror(NULL);
		exit(1);
	}
	if (vfork())
	{
		dup2(fd, STDOUT_FILENO);
		printf("1234\n");
	}
	else
		wait(&ret);
	return (0);
}
