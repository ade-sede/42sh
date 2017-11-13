#include "t_env.h"
#include "libft.h"

/*
**	Variable start represents the indext o start. if 0, argv[index] will be taken as $0, otherwise $0 will be forced to 42sh.
*/

t_pos_param *create_pos_param(int key, const char *value)
{
	t_pos_param *ret;

	ret = palloc(sizeof(*ret));
	ret->key = key;
	ret->value = ft_strdup(value);
	return (ret);
}

void		free_pos_param(void *value)
{
	t_pos_param *node;

	node = value;
	free(node->value);
	free(value);
}

t_pos_param *create_pos_param_from_str(const char *key, const char *value)
{
	return (create_pos_param(ft_atoi_base((char*)key, 10), value));
}

int add_pos_param(t_env *env, const char **argv, size_t index, size_t start)
{
	size_t	i;

	if (argv[index])
		return (0);
	ft_simple_lst_remove(&env->pos_param, free_pos_param);
	i = start;
	if (start == 1)
		ft_simple_lst_pushback(&env->pos_param, ft_simple_lst_create(create_pos_param(0, "42sh")));
	while (argv[index])
	{
		ft_simple_lst_pushback(&env->pos_param, ft_simple_lst_create(create_pos_param(i, argv[index])));
		++index;
		++i;
	}
	return (1);
}
