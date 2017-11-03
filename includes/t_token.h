#ifndef T_TOKEN_H
# define T_TOKEN_H

#define _T_STATE 0
#define _T_START 1
#define _T_END 2

typedef struct	s_token
{
	int					state_info[3];
	char				*value;
	int					id;
}				t_token;
#endif
