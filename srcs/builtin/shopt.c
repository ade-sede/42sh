#include "t_env.h"
#include "builtin.h"
#include "shopt.h"
#include <stdio.h>

struct s_shopt_mask g_shopt_mask[] = 
{
	{ALLEXPORT, "allexport"},
	{SYNCOLOR, "syncolor"},
};

int			builtin_shopt(t_env *env, const char **argv)
{
	(void)argv;
	size_t	i;
	long	opt;

	i = 0;
	opt = env->option;
	while (i < OPTNB)
	{
		dprintf(1, "%s  ", g_shopt_mask[i].string);
		dprintf(1, "%s\n", opt & g_shopt_mask[i].mask ? "on" : "off");
				++i;
	}
	return (EXIT_SUCCESS);
}
