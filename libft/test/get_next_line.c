/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 13:54:55 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/01 13:59:03 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <stdio.h>
#include "fcntl.h"

int		main(int ac, char *av[])
{
	char	*line;
	int		fd;
	char	*file;

	file = (ac == 1) ? "Makefile" : av[1];
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line))
		printf("%s\n", line);
	return (0);
}
