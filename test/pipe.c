/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 10:35:30 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/21 13:23:40 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define WRITE_END 1
#define READ_END 0

int		main(void)
{
	int		*fd1;
	int		*fd2;
	int		out_save1;
	int		in_save1;
	int		out_save2;
	int		in_save2;
	pid_t	child1;
	pid_t	child2;
	pid_t	child3;
	char	buff[4096];
	

	bzero(buff, 4096);
	/* Starting first pipe */
	fd1 = malloc(sizeof(*pipe) * 3);
	fd1[2] = -1;
	if (pipe(fd1) == -1)
		printf("Error opening pipe 1\n");

	/* Saving 1 for pipe 1*/
	out_save1 = dup(1);

	/* Launching cmd 1 */
	child1 = fork();
	if (child1 == 0)
	{
		/* Link 1 to write_end of p1*/
		dup2(fd1[WRITE_END], 1);
		exit(system("ls"));
	}
	else
	{
		wait(&child1);
		dprintf(2, "Done with cmd1 \n");
	}


	/* Restoring 1 after pipe 1*/
	dup2(1, out_save1);

	/* Saving 1 for pipe2*/
	out_save2 = dup(1);

	/* Saving 0 for pipe1*/
	in_save1 = dup(0);

	/* Starting 2nd pipe */
	fd2 = malloc(sizeof(*pipe) * 3);
	fd2[2] = -1;
	if (pipe(fd2) == -1)
		printf("Error opening pipe 2\n");

	/* Starting 2nd command */
	child2 = fork();
	if (child2 == 0)
	{
		/* Link 0 to read_end of p1 */
		dup2(fd1[READ_END], 0);
		read(0, buff, 4096);
		/* dprintf(2, "Command 2 received from cmd 1 :\n"MAG"#"CYN"%s"MAG"#\n"RESET, buff); */
		/* Link 1 to write_end of p2*/
		dup2(fd2[WRITE_END], 1);

		exit(system("echo yup"));
	}
	else
	{
		wait(&child2);
		dprintf(2, "Done with cmd2 \n");
	}

	/* Restoring 1 after pipe1 */
	dup2(1, out_save2);

	/* Restoring 0 after pipe1 */
	dup2(0, in_save1);

	/* Saving 0 for pipe2 */
	in_save2 = dup(0);
	close(fd1[0]);
	close(fd1[1]);

	/* Starting cmd3 */
	bzero(buff, 4096);
	child3 = fork();
	if (child3 == 0)
	{
		/* Link 0 to read_end of p2 */
		dup2(fd2[READ_END], 0);
		read(0, buff, 4096);
		/* dprintf(2, "Command 3 received from cmd 2 :\n"MAG"#"CYN"%s"MAG"#\n"RESET, buff); */

		exit(system("ls -l"));
	}
	else
	{
		wait(&child3);
		dprintf(2, "Done with cmd3 \n");
	}

	/* Restoring 0 after p2 */
	dup2(0, in_save2);
	close(fd2[0]);
	close(fd2[1]);
	return (0);
}
