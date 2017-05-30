/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 20:40:07 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/02 14:55:32 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"
#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	main(int ac, char **av)
{
	int	fd = 0;
	char	*line = NULL;
	int	ret;
	
	if (av[1] != NULL)
		fd = open(av[1], O_RDONLY);
	while (1)
	{
		while ((ret = get_next_line(fd, &line)) >= 0)
			ft_printf("line = %s\n", line);

	}
}
