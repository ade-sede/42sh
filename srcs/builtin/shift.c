#include "t_env.h"
#include "local.h"
#include "libft.h"
#include "failure.h"

int			fisrt_err(int *n, const char **argv)
{
	size_t		len;

	len = ft_arraylen(argv);
	if (len > 2)
		return (1);
	if (len == 1)
		*n = 1;
	else
		*n = ft_atoi_base((char*)argv[1], 10);
	return (0);
}

int			builtin_shift(t_env *env, const char **argv)
{
	int			n;
	size_t		n_tmp;
	t_list		*node_del;
	t_list		*del_next;;
	t_list		*node_shift;
	t_pos_param	*pos_param;
	char		*tmp_max_param;


	if (fisrt_err(&n, argv))
		return (investigate_error(1, "shift: ", "Too many arguments", EXIT_FAILURE));
	tmp_max_param = local_get_value(env->local, "#");
	if (!tmp_max_param)
			return (EXIT_FAILURE);
	if (n == 0)
		return (EXIT_FAILURE);
	if (n > ft_atoi_base(tmp_max_param, 10))
		return (EXIT_FAILURE);
	n_tmp = n;
	node_del = get_pos_param_node(env->pos_param, 1);
	node_shift = get_pos_param_node(env->pos_param, n + 1);
	while (n_tmp && node_del)
	{
		del_next = node_del->next;
		ft_simple_lst_del_one(&env->pos_param, node_del, free_pos_param);
		node_del = del_next;
		--n_tmp;
	}
	while (node_shift)
	{
		pos_param = node_shift->data;
		pos_param->key -= n;
		node_shift = node_shift->next;
	}
	return (EXIT_SUCCESS);
}
