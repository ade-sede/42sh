#include "history.h"
#include "builtin.h"
#include "env.h"
#include <stdio.h>
#include "get_next_line.h"
#include "libft.h"
#include "printf.h"

static t_history_opt	g_history_opt[] =
{
	/* {"-a", &handle_a}, */
	/* {"-n", &handle_n}, */
	{"-r", &handle_r},
	/* {"-w", &handle_w}, */
	/* {"-d", &handle_d}, */
	/* {"-c", &handle_c}, */
	{NULL, NULL}
};

static void	print_history_item(t_list_d *item, size_t i)
{
	ft_printf("%8zu  %s\n", i, item->data);
}

const char		**handle_numeric_arg(t_hist *h, const char **argv, int n, int *ret)
{
	t_list_d	*nth_node;

	if (*(argv + 1))
		*ret = return_failure("Too many arguments", NULL);
	else
		if (h->list)
		{
			nth_node = ft_double_lst_get_n(h->list->first, n);
			ft_double_lst_iteri(nth_node, NULL, &print_history_item, -1);
		}
	return (argv + 1);
}
const char		**handle_options(t_hist *h, const char **argv, int *ret)
{
	size_t	i;
	int		error;
	int		done;

	error = EXIT_SUCCESS;
	done = FALSE;
	i = 0;
	while (!done && g_history_opt[i].key)
	{
		if ((done = ft_strequ(g_history_opt[i].key, *argv)))
			argv = g_history_opt[i].f(h, argv + 1, &error);
	}
	if (!done || error != EXIT_SUCCESS)
		*ret = return_failure("History: invalid option --", *argv);
	return (argv);
}

int		parse_options(t_hist *h, const char **argv)
{
	int		ret;
	int		n;

	n = -1;
	ret = EXIT_SUCCESS;
	while (*argv)
	{
		if (ret == EXIT_SUCCESS && **argv == '-')
			argv = handle_options(h, argv, &ret);
		else if (ret == EXIT_SUCCESS && *argv && ft_atoi_safe(*argv, &n) && n >= 0)
			argv = handle_numeric_arg(h, argv, n, &ret);
		else
			return (return_failure("history : numeric argument or option required", NULL));
		if (ret != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	builtin_history(t_env *env, const char **argv)
{
	t_hist	*h;

	(void)env;
	h = singleton_hist();
	if (argv[1] == NULL)
	{
		if (h->list)
			ft_double_lst_iteri(h->list->last, NULL, &print_history_item, -1);
		return (EXIT_SUCCESS);
	}
	return (parse_options(h, argv + 1));
}
