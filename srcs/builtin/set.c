#include "local.h"
#include "builtin.h"
#include "t_env.h"
#include "shopt.h"
#include "failure.h"
#include "get_opt.h"

static t_option g_option[] = {
	{1, "o", OPTION_STRING, "shell option", "Set / Unset a shell option"},
	{0, NULL, 0, NULL, NULL}
};

static t_programinfo g_programinfo = {
	"set",
	"aaaa",
	g_option,
	NULL,
	0,
	0,
	1,
	0,
	NULL,
	0,
	0
};

static struct s_shopt_id g_shopt_id[] = 
{
	{ALLEXPORT, "allexport"},
	{-1, NULL},
};

static int	set_shell_opt(t_env *env, int sign, const char *option_value)
{
	size_t	i;

	i = 0;
	while (g_shopt_id[i].value && !ft_strequ(g_shopt_id[i].value, option_value))
		++i;
	if (g_shopt_id[i].value == NULL)
		return (0);
	if (sign == '-')
		env->option |= g_shopt_id[i].id;
	if (sign == '+')
		env->option ^= g_shopt_id[i].id;
	return (1);
}

int			builtin_set(t_env *env, const char **argv)
{
	int		opt_id;
	size_t	argc;

	argc = ft_arraylen(argv);
	if (argc == 1)	// DISPLAY ALL
		;
	opt_init(&g_programinfo, argc, argv);
	while (g_programinfo.argerr == 0 && (opt_id = get_opt(&g_programinfo) > 0))
	{
		if (opt_id == 1)
			set_shell_opt(env, g_programinfo.min, g_programinfo.argopt);
	}
	if (g_programinfo.argerr)
		return (EXIT_FAILURE);
	add_pos_param(env, argv, g_programinfo.argcur, 1);
	return (EXIT_SUCCESS);
}
