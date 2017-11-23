#include "t_env.h"
#include "libft.h"
#include "local.h"

t_pos_param		*create_pos_param(int key, const char *value)
{
	t_pos_param *ret;

	ret = palloc(sizeof(*ret));
	ret->key = key;
	ret->value = ft_strdup(value);
	return (ret);
}

void			free_pos_param(void *value)
{
	t_pos_param *node;

	node = value;
	free(node->value);
	free(value);
}

t_pos_param		*create_pos_param_from_str(const char *key, const char *value)
{
	return (create_pos_param(ft_atoi_base((char*)key, 10), value));
}

/*
**	Variable start represents the indext o start. if 0, argv[index] will be
**	taken as $0, otherwise $0 will be forced to 42sh.
*/

t_list			*get_pos_param_node(t_list *first, int key)
{
	t_pos_param	*tmp;

	while (first)
	{
		tmp = first->data;
		if (tmp->key == key)
			return (first);
		first = first->next;
	}
	return (NULL);
}
