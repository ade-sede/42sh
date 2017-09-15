#include "env.h"
#include "builtin.h"
#include "libft.h"
#include "printf.h"
#include <stdio.h>

static void		print_alias(t_list *alias)
{
	ft_putendl(alias->data);
}

t_list	*find_alias(t_list *alias, const char *argv, size_t len)
{
	while (alias && ft_strnequ(alias->data, argv, len) == 0)
		alias = alias->next;
	return (alias);
}

int				builtin_alias(t_env *env, const char **argv)
{
	int		eq_index;
	int		argc;
	int		i;
	t_list	*node;
	int		ret;

	i = 1;
	ret = EXIT_SUCCESS;
	argc = ft_arraylen(argv);
	if (argc == 1)
		ft_simple_lst_foreach(env->alias, NULL, print_alias);
	while (i < argc)
	{
		eq_index = ft_strichr(argv[i], '=');
		if (eq_index == -1)
		{
			node = find_alias(env->alias, argv[i], ft_strlen(argv[i]));
			if (node)
			{
				ft_putstr(node->data);
			}
			else
				ret = EXIT_FAILURE;
		}
		else
		{
			node = find_alias(env->alias, argv[i], eq_index + 1);
			if (node)
				node->data = ft_strchange(node->data, ft_strdup(argv[i]));
			else
				ft_simple_lst_pushback(&env->alias, \
						ft_simple_lst_create(ft_strdup(argv[i])));
			ret = EXIT_SUCCESS;
		}
		i++;
	}
	return (ret);
}

int			builtin_unalias(t_env *env, const char **argv)
{
	int		argc;
	int		i;
	t_list	*node;
	int		ret;

	i = 1;
	ret = EXIT_SUCCESS;
	argc = ft_arraylen(argv);
	if (argc == 1)
		return (return_failure(NULL, "unalias : Argument required"));
	while (i < argc)
	{
		node = find_alias(env->alias, argv[i], ft_strlen(argv[i]));
		if (node)
		{
			ft_simple_lst_del_one(&env->alias, node, ft_free);
			ret = EXIT_SUCCESS;
		}
		else
		{
			return_failure("alias not found : ", argv[i]);
			ret = EXIT_FAILURE;
		}
		i++;
	}
	return (ret);
}
