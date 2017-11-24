/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:13:59 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local.h"
#include "builtin.h"
#include "exec.h"

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

int				exec_function(t_ast *fct_body, char **av)
{
	if (av)
		add_pos_param(singleton_env(), (const char**)av, 0, 0);
	return (exec(fct_body));
}
