#include "t_env.h"
#include "libft.h"
#include "shopt.h"

struct s_shopt_mask g_shopt_mask[OPTNB];

/*
**	Sign is '-' if value must be set '+' if it must be
**	unset
*/

#include <stdio.h>

int	set_shell_opt(t_env *env, int sign, const char *option_value)
{
	size_t	i;

	i = 0;
	while (i != OPTNB && !ft_strequ(g_shopt_mask[i].string, option_value))
		++i;
	if (i == OPTNB)
		return (0);
	if (sign == '-')
		env->option |= g_shopt_mask[i].mask;
	if (sign == '+')
		if (env->option & g_shopt_mask[i].mask)
			env->option ^= g_shopt_mask[i].mask;
	return (1);
}
