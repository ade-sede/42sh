#include "history.h"
#include "builtin.h"
#include "env.h"
#include <stdio.h>

#include "get_next_line.h"
static t_history_opt	g_history_opt[] =
{
	{"-a", &handle_a},
	//{"-n", &handle_n},
	{"-r", &handle_r},
	//{"-w", &handle_w},
	//{"-d", &handle_d},
	//{"-c", &handle_c},
	{NULL, NULL}
};

static void	print_history_item(t_list_d *item)
{
	static	size_t i = 0;

	if (item == NULL)
	{
		i = 0;
		return ;
	}
	printf("%8zu  %s\n", i, item->data);
	i++;
}

const char	**handle_a(t_hist *h, const char **argv, int *error)
{
	(void)h;
	if (argv == NULL) 
		*error = return_failure("option -- a requires an argument", NULL);
	printf("We did it\n");
	return (argv + 1);
}

const char	**handle_r(t_hist *h, const char **argv, int *error)
{
	int		fd;
	char		*line;
	t_list_d	*list;
	
	if (argv == NULL)
	{
		*error = return_failure("option -- r requires an argument", NULL);
		return (NULL);
	}
	if ((fd = open(*argv, O_RDONLY)) == -1)
	{
		*error = return_failure("bad file: ", *argv);
		return (NULL);
	}
	while (get_next_line(fd, &line))
	{
		list = ft_double_lst_create(line);
		if (h->list == NULL)
			h->list = ft_create_head(list);
		else
			ft_double_lst_add(&(h->list), list); 
	}
	return (argv + 1);
}

static int	handle_options(t_hist *h, const char **argv)
{
	size_t		i;
	int		error;
	int		n;
	int		done;
	t_list_d	*nth;

	nth = NULL;
	error = 0;
	n = -1;
	while (*argv)
	{
		i = 0;
		if (*argv && ft_atoi_safe(*argv, &n) && n >= 0)
		{
			if (argv[1] != NULL)
				return (return_failure("to many arguments", NULL));
			if (h->list)
			{
				nth = ft_double_lst_get_n(h->list->first, n);
				ft_double_lst_for_n(nth, (size_t)n, &print_history_item, -1);
			}
			argv++;
		}
		else if (**argv == '-')
		{
			done = 0;
			while (g_history_opt[i].key)
			{
				if (!done && (done = ft_strequ(*argv, g_history_opt[i].key)))
					argv = g_history_opt[i].f(h, argv + 1, &error);
				i++;
			}
			if (!done)
				return (return_failure("Invalid options -- ", *argv));
			else if (error)
				return (EXIT_FAILURE);
		}
		else
			return (return_failure("history numeric argument required", NULL));
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
		{
			ft_double_lst_foreach(h->list->last, NULL, &print_history_item, -1);
			print_history_item(NULL);
		}
		return (EXIT_SUCCESS);
	}
	return (handle_options(h, argv + 1));
}
