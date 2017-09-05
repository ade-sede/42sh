/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 12:42:06 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/05 15:27:05 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "color.h"
#include <stdio.h>
#define READ_END 0
#define WRITE_END 1

int		main(void)
{
	dprintf(2, MAG"In test\n"RESET);
	pid_t	c0;
	pid_t	c1;
	int		p0[2];
	int		p1[2];
	int		ret = 0;

	dprintf(2, MAG"qweqweq\n"RESET);
	if (pipe(p0) != 0 || pipe(p1) != 0)
	{
		dprintf(2, RED"Impossible to create pipes\n"RESET);
		exit(1);
	}
	c0 = fork();
	if (c0 == 0) // CHILD 0 -> Is on the left of a pipe.
	{
		dprintf(2, RED"Inside child 1\n"RESET);

		/* Write on the pipe to its right */
		dup2(p0[WRITE_END], STDOUT_FILENO);
		close(p0[READ_END]);

		/* exec */
		ret = system("base64 /dev/urandom");
		dprintf(2, "Child 0 returned %d\n", ret);
		exit(ret);
	}
	else // PARENT (simultaneous to child0)
	{
		c1 = fork();
		if (c1 == 0) // CHILD 1 -> Is between pipes
		{
			dprintf(2, RED"Inside child 2\n"RESET);
			
			/* Read from the pipe on its left */
			dup2(p0[READ_END], STDIN_FILENO);
			/* close(p0[WRITE_END]); */

			/* Write to the pipe on its right */
			dup2(p1[WRITE_END], STDOUT_FILENO);
			close(p1[READ_END]);

			/* exec */
			ret = system("head -c 1000");
			printf("\n");
			dprintf(2, "Child 1 returned %d\n", ret);
			exit(ret);
		}
		else // PARENT (simultaneous to both child0 and child1) Here, both commands are currently being executed.
		{

			close(p0[READ_END]);
			close(p0[WRITE_END]);

			/* Read from the pipe on its left */
			int	save = dup(STDIN_FILENO);
			dup2(p1[READ_END], STDIN_FILENO);
			close(p1[WRITE_END]);

			system("wc");
			/* Restore fd 0 as the STD IN */
			dup2(0, save);
		}
	}
	return (0);
}
