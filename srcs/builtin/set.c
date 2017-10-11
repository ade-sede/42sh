#include "local.h"
#include "builtin.h"
#include "env.h"
#include "ft_getopt.h"
#include "option.h"

#include <stdio.h>

static void	print_t_option_id(t_option_id id)
{
	if (id == ALLEXPORT)
		write(1, "allexport  ", 11);
	else if (id == INTERACTIVE)
		write(1, "interactive", 11);
	else
		write(1, "unknown    ", 11);
}

static int	print_list(t_list *list, t_list *pos)
{
	t_list		*tmp_list;
	t_list		*tmp_pos;

	tmp_list = list;
	while (tmp_list != NULL)
	{
		ft_putendl(tmp_list->data);
		tmp_list = tmp_list->next;
	}
	tmp_pos = pos;
	while (tmp_pos != NULL)
	{
		printf("pos = [%s]\n", tmp_pos->data);
		tmp_pos = tmp_pos->next;
	}
	return (EXIT_SUCCESS);
}

static void	print_all_option(t_env *env)
{
	int		x;
	long	mask;

	x = 0;
	mask = 1;
	while (x < 31)
	{
		print_t_option_id(mask);
		write(1, "\t\n", 1);
		write(1, (((env->option & mask) == mask) ? "on\n" : "off\n"),
				(((env->option & mask) == mask) ? 3 : 4));
		mask = mask << 1;
		x++;
	}
}

static void	print_current_option(t_env *env)
{
	int		x;
	long	mask;

	x = 0;
	mask = 1;
	while (x < 31)
	{
		if (((env->option & mask) == mask))
		{
			write(1, "set -o ", 7);
			print_t_option_id(mask);
			write(1, "\n", 1);
		}
		mask = mask << 1;
		x++;
	}
}

static int	match_name_option(const char *argv)
{
	if (strcmp("allexport", argv) == 0)
		return (ALLEXPORT);
	else if (strcmp("interactive", argv) == 0)
		return (INTERACTIVE);
	else
		return (-1);
}

static void	add_option(t_env *env, int *x, const char **argv)
{
	int		option_id;

	if (argv[*x][2] != '\0')
	{
		if ((option_id = match_name_option(argv[*x])) != -1)
			env->option = env->option | option_id;
	}
	else if (argv[*x + 1] != NULL)
	{
		*x = *x + 1;
		if ((option_id = match_name_option(argv[*x])) != -1)
			env->option = env->option | option_id;
	}
	else
	{
		print_current_option(env);
	}
}

static void	remove_option(t_env *env, int *x, const char **argv)
{
	int		option_id;

	if (argv[*x][2] != '\0')
	{
		if ((option_id = match_name_option(argv[*x])) != -1)
			env->option = env->option & ~option_id;
	}
	else if (argv[*x + 1] != NULL)
	{
		*x = *x + 1;
		if ((option_id = match_name_option(argv[*x])) != -1)
			env->option = env->option & ~option_id;
	}
	else
	{
		print_all_option(env);
	}
}

static void	set_pos_par(t_env *env, int x, int argc, const char **argv)
{
	int			nbr_pos_par;

	nbr_pos_par = 1;
	while (x < argc)
	{
		if (nbr_pos_par <= 1)
			ft_simple_lst_remove(&env->pos_par, ft_free);
		ft_simple_lst_pushback(&env->pos_par, ft_simple_lst_create(
					ft_strjoin3_free(ft_itoa(nbr_pos_par), "=",
						(char *)argv[x], 0b100)));
		nbr_pos_par++;
		x++;
	}
}

int			builtin_set(t_env *env, const char **argv)
{
	int			x;
	int			argc;

	argc = ft_arraylen(argv);
	if (argc == 1)
		return (print_list(env->local, env->pos_par));
	x = 1;
	while (x < argc)
	{
		if (argv[x][0] == '-' && argv[x][1] == 'o')
			remove_option(env, &x, argv);
		else if (argv[x][0] == '+' && argv[x][1] == 'o')
			add_option(env, &x, argv);
		else if (argv[x][0] == '-' && argv[x][0] == '-')
		{
			x++;
			break ;
		}
		else
			break ;
		x++;
	}
	set_pos_par(env, x, argc, argv);
	return (EXIT_SUCCESS);
}
