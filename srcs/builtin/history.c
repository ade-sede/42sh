/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:13:46 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "history.h"
#include "get_opt.h"
#include "printf.h"
#include "builtin.h"

static int	print_history(t_hist *hist, int count)
{
	t_list_d	*node;
	t_list_d	*end;
	size_t		i;

	i = 1;
	if (!hist->list || !hist->list->first)
		return (EXIT_FAILURE);
	node = hist->list->first;
	if (count == -1)
		end = NULL;
	else
		end = ft_double_lst_get_n(hist->list->first, count);
	while (node != end)
	{
		ft_dprintf(2, "-%u %s\n", i, node->data);
		++i;
		node = node->next;
	}
	return (EXIT_SUCCESS);
}

static int	launch_opt(const char ***argv)
{
	if (!**argv)
		return (EXIT_FAILURE);
	if (ft_strequ(**argv, "-c"))
	{
		++(*argv);
		return (builtin_history_c(singleton_hist()));
	}
	else if (ft_strequ(**argv, "-w"))
	{
		++(*argv);
		return (builtin_history_w(singleton_hist(), **argv));
	}
	else if (ft_strequ(**argv, "-r"))
	{
		++(*argv);
		return (builtin_history_r(singleton_hist(), **argv));
	}
	else if (ft_strequ(**argv, "-p"))
	{
		++(*argv);
		return (builtin_history_p(singleton_hist(), **argv));
	}
	return (EXIT_FAILURE);
}

int			builtin_history(t_env *env, const char **argv)
{
	size_t			argc;
	int				ret;
	const char		**s;

	s = argv;
	ret = EXIT_SUCCESS;
	argc = ft_arraylen(argv);
	if (argc == 1 || argc == 2)
	{
		if (argc == 2 && ft_str_isdigit(argv[1]) && *argv[1] != '-')
			return (print_history(singleton_hist(), \
						ft_atoi_base((char*)argv[1], 10)));
		else if (argc == 1)
			return (print_history(singleton_hist(), -1));
	}
	++argv;
	while (*argv && ret == EXIT_SUCCESS)
		ret = launch_opt(&argv);
	(void)env;
	argv = s;
	return (ret);
}
