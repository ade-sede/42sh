/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 15:09:37 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/17 17:06:10 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H
# include <stdlib.h>

# define READ_END 0
# define WRITE_END 1

typedef struct	s_pipe
{
	int			*p;
	pid_t		pid;
}				t_pipe;

/*
**	In file srcs/parser/t_pipe.c
*/

t_pipe			*create_pipe(int *p);
void			free_pipe(void *pipe);
#endif
