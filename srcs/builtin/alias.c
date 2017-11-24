#include "t_env.h"
#include "builtin.h"
#include "libft.h"
#include "printf.h"

static void	print_alias(t_list *alias)
{
	ft_putendl(alias->data);
}

t_list		*find_alias(t_list *alias, const char *argv, size_t len)
{
	while (alias && ft_strnequ(alias->data, argv, len) == 0)
		alias = alias->next;
	return (alias);
}

static void	create_alias(t_env *env, const char *argv, int eq_index, int *ret)
{
	t_list	*node;

	node = find_alias(env->alias, argv, eq_index + 1);
	if (node)
		node->data = ft_strchange(node->data, cl_strdup(argv));
	else
		ft_simple_lst_pushback(&env->alias, \
				ft_simple_lst_create(cl_strdup(argv)));
	*ret = EXIT_SUCCESS;
}

static void	show_alias(t_env *env, const char *argv, int *ret)
{
	t_list	*node;

	node = find_alias(env->alias, argv, ft_strlen(argv));
	if (node)
		print_alias(node);
	else
		*ret = EXIT_FAILURE;
}

int			builtin_alias(t_env *env, const char **argv)
{
	ssize_t	eq_index;
	int		argc;
	int		i;
	int		ret;

	i = 0;
	ret = EXIT_SUCCESS;
	argc = ft_arraylen(argv);
	if (argc == 1)
		ft_simple_lst_foreach(env->alias, NULL, print_alias);
	while (++i < argc)
	{
		eq_index = ft_strichr(argv[i], '=');
		if (eq_index == -1)
			show_alias(env, argv[i], &ret);
		else if ((size_t)eq_index != ft_strlen(argv[i]) - 1)
			create_alias(env, argv[i], eq_index, &ret);
	}
	return (ret);
}
