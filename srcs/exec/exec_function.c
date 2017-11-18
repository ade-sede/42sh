#include "exec.h"
#include "local.h"
#include "builtin.h"

t_lst_func		*get_function(t_env *env, char *cmd_name)
{
	t_lst_func		*tmp;

	tmp = env->first_func;
	while (tmp)
	{
		if (ft_strequ(tmp->fname, cmd_name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

/*
**	cmd_suffix       :            io_redirect
**	                 | cmd_suffix io_redirect
**	                 |            WORD
**	                 | cmd_suffix WORD
*/

int		exec_function(t_ast *fct_body, char **av)
{
	add_pos_param(singleton_env(), (const char**)av, 0, 0);
	return (exec(fct_body));
}
