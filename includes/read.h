#ifndef READ_H
# define READ_H

#include "env.h"

#define USG "read [-rs] [-u fd] [-p prompt] [-n nchars] [-d delim] [name ...]"

#define R 1
#define S 2

typedef struct s_read
{
	char			*prompt;
	int				nchars;
	int				fd;
	unsigned char	flags;
	char			delim;
	char			padding[6]; // TODO
}				t_read;

/*
** In read.c
*/

int				builtin_read(t_env *env, const char **argv);

//unsigned char	read_builtin();
char			parse_read(char *arg, t_read *option, char ***args);
char			*read_retrieve(t_read options);

#endif

