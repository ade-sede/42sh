#include "exec.h"
#include "builtin.h"

t_ast	*get_function(t_env *env, char *cmd_name)
{
	t_lst_func		*tmp;

	tmp = env->first_func;
	while (tmp)
	{
		if (ft_strequ(tmp->fname, cmd_name))
			return (tmp->fct_body);
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
	set_pos_par(singleton_env(), 1, ft_arraylen((const char **)av), (const char **)av); //TODO: attention
	return (exec(fct_body));
}
