#include "t_env.h"
#include "libft.h"
#include "local.h"


#include <stdio.h>

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

/*
**	Variable start represents the indext o start. if 0, argv[index] will be
**	taken as $0, otherwise $0 will be forced to 42sh.
*/

t_list	*get_pos_param_node(t_list *first, int key)
{
	t_pos_param *tmp;

	while (first)
	{
		tmp = first->data;
		if (tmp->key == key)
			return (first);
		first = first->next;
	}
	return (NULL);
}

int add_pos_param(t_env *env, const char **argv, size_t index, size_t start)
{
	size_t	i;
	char	*all_param;
	char	*nb_param;

	if (!argv[index])
		return (0);
	all_param = NULL;
	ft_simple_lst_remove(&env->pos_param, free_pos_param);
	i = start;
	if (i == 1)
		ft_simple_lst_pushback(&env->pos_param, ft_simple_lst_create(create_pos_param(0, "42sh")));
	while (argv[index])
	{
		ft_simple_lst_pushback(&env->pos_param, ft_simple_lst_create(create_pos_param(i, argv[index])));
		if (i > 0)
		{
			if (all_param)
				all_param = ft_strchange(all_param, ft_strsurround(all_param, " ", argv[index]));
			else
				all_param = ft_strdup(argv[index]);
		}
		++index;
		++i;
	}
	local_add_change_from_key_value(&env->local, "@", all_param);
	local_add_change_from_key_value(&env->local, "*", all_param);
	nb_param = ft_itoa_base(i - 1, 10);
	local_add_change_from_key_value(&env->local, "#", nb_param);
	free(nb_param);
	return (1);
}
