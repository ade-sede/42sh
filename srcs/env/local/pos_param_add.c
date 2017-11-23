#include "t_env.h"
#include "libft.h"
#include "local.h"

static int		add_free_param(char **all_param, t_env *env, size_t i)
{
	char		*nb_param;

	if (*all_param)
	{
		local_add_change_from_key_value(env, "@", *all_param);
		local_add_change_from_key_value(env, "*", *all_param);
		nb_param = ft_itoa_base(i - 1, 10);
		local_add_change_from_key_value(env, "#", nb_param);
		free(nb_param);
		ft_strdel(all_param);
	}
	return (1);
}

int				add_pos_param(t_env *env, const char **argv,
		size_t index, size_t start)
{
	char		*all_param;

	if (!argv[index])
		return (0);
	all_param = NULL;
	ft_simple_lst_remove(&env->pos_param, free_pos_param);
	if (start)
		ft_simple_lst_pushback(&env->pos_param,
				ft_simple_lst_create(create_pos_param(0, "42sh")));
	while (argv[index])
	{
		ft_simple_lst_pushback(&env->pos_param,
				ft_simple_lst_create(create_pos_param(start, argv[index])));
		if (start > 0)
		{
			if (all_param)
				all_param = ft_strchange(all_param,
						ft_strsurround(all_param, " ", argv[index]));
			else
				all_param = ft_strdup(argv[index]);
		}
		++index;
		++start;
	}
	return (add_free_param(&all_param, env, start));
}
