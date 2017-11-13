#ifndef SHOPT_H
# define SHOPT_H
# include "t_env.h"

/*
**	Defining flags for options
*/

/*
**	If you edit OPTNB, recompile the program.
*/

# define OPTNB 1U
# define ALLEXPORT 0b1L

struct s_shopt_mask
{
	long	mask;
	char	*string;
};

extern struct s_shopt_mask g_shopt_mask[OPTNB];

int	set_shell_opt(t_env *env, int sign, const char *option_value);
#endif
