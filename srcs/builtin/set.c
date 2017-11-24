#include "printf.h"
#include "local.h"
#include "builtin.h"
#include "t_env.h"
#include "shopt.h"
#include "failure.h"
#include "get_opt.h"
#include <stdio.h>

static t_option g_option[] = {
	{1, "o", OPTION_STRING, "shell option", "Set / Unset a shell option"},
	{0, NULL, 0, NULL, NULL}
};

static void	pi_set(t_programinfo *pi)
{
	pi->desc = "Assign positional parameters / set unset shell variables";
	pi->list_option = g_option;
	pi->argv = NULL;
	pi->argc = 0;
	pi->argparg = 0;
	pi->argcur = 1;
	pi->argpos = 0;
	pi->argopt = NULL;
	pi->argerr = 0;
	pi->min = 0;
}

static int	display_all(t_env *env)
{
	t_list			*local_list;
	t_local			*local;
	t_list			*pos_param_list;
	t_pos_param		*pos_param;

	local_list = env->local;
	pos_param_list = env->pos_param;
	while (local_list)
	{
		local = local_list->data;
		ft_putstr_fd(local->key, 2);
		ft_putstr_fd("=", 2);
		ft_putstr_fd(local->value, 2);
		ft_putchar_fd('\n', 2);
		local_list = local_list->next;
	}
	while (pos_param_list)
	{
		pos_param = pos_param_list->data;
		dprintf(2, "%d=", pos_param->key);
		ft_putstr_fd(pos_param->value, 2);
		ft_putchar_fd('\n', 2);
		pos_param_list = pos_param_list->next;
	}
	return (1);
}

int			builtin_set(t_env *env, const char **argv)
{
	int				opt_id;
	size_t			argc;
	t_programinfo	pi;

	pi.progname = "set";
	pi_set(&pi);
	argc = ft_arraylen(argv);
	if (argc == 1)
	{
		display_all(env);
		return (EXIT_SUCCESS);
	}
	opt_init(&pi, argc, argv);
	while (pi.argerr == 0 && (opt_id = get_opt(&pi) > 0))
	{
		if (opt_id == 1)
			set_shell_opt(env, pi.min, pi.argopt);
	}
	if (pi.argerr)
		return (EXIT_FAILURE);
	add_pos_param(env, argv, pi.argcur, 1);
	return (EXIT_SUCCESS);
}
