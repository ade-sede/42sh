#include "local.h"
#include "builtin.h"
#include "t_env.h"
#include "option.h"

int			builtin_set(t_env *env, const char **argv)
{
	(void)env, (void)argv;
	return (EXIT_SUCCESS);
}
