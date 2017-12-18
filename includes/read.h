/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:38 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:42 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_H
# define READ_H

# include "termios.h"
# include "t_env.h"

# define USG "read [-rs] [-u fd] [-p prompt] [-n nchars] [-d delim] [name ...]"

# define R 1
# define S 2

# define SAVETERM	0
# define NO_ICANON	1
# define NO_ECHO	2
# define RESTORTERM	-1
# define IFS_DEFAULT " \t\n"

typedef struct	s_read
{
	char			*prompt;
	int				nchars;
	int				fd;
	unsigned char	flags;
	char			delim;
	struct termios	term;
}				t_read;

/*
** In read.c
*/

int				builtin_read(t_env *env, const char **argv);

char			parse_read(char *arg, t_read *option, char ***args);
char			*read_retrieve(t_read options);
char			*read_get_input(t_read read);
char			*read_get_rcinput(t_read options);
char			read_parse_argv(const char **argv);
char			read_parse_option(t_read *options, const char ***argv);
void			read_backslash(char **line, char **word, char quote);
char			failure_read(char status, char *arg);
#endif
