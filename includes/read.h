/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:38 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:45 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_H
# define READ_H

# include "t_env.h"

# define USG "read [-rs] [-u fd] [-p prompt] [-n nchars] [-d delim] [name ...]"

# define R 1
# define S 2

typedef struct	s_read
{
	char			*prompt;
	int				nchars;
	int				fd;
	unsigned char	flags;
	char			delim;
	char			padding[6];
}				t_read;

/*
** In read.c
*/

int				builtin_read(t_env *env, const char **argv);

char			parse_read(char *arg, t_read *option, char ***args);
char			*read_retrieve(t_read options);
char			*read_get_input(t_read read);
char			*read_get_rcinput(t_read options);

#endif
